#!/usr/bin/env bash
# mayhem/build.sh — build the esphome-jk-bms fuzz harnesses and upstream's C++ unit suite.
#
# The components under components/ are ESPHome external components; upstream builds and tests them
# inside an ESPHome checkout on the host platform (run-cpp-tests.sh -> script/cpp_unit_test.py). That
# codegen step only produces config headers (committed as mayhem/esphome_gen/) and a list of sources;
# this script compiles the same ESPHome host core straight from the pinned ESPHome source in
# $ESPHOME_SRC (/opt/toolchains/deps, see mayhem/Dockerfile) plus the components from this tree.
#   fuzz build : ESPHome core + components with $SANITIZER_FLAGS $DEBUG_FLAGS -> /mayhem/fuzz_*(-standalone)
#   test build : same sources with upstream's normal flags (no sanitizers) + googletest -> mayhem/out/cpp_unit_tests
set -euo pipefail
[ -n "${SOURCE_DATE_EPOCH:-}" ] || unset SOURCE_DATE_EPOCH
: "${SANITIZER_FLAGS=-fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer}"
: "${DEBUG_FLAGS:=-g -gdwarf-3}"
: "${CC:=clang}" ; : "${CXX:=clang++}" ; : "${LIB_FUZZING_ENGINE:=-fsanitize=fuzzer}"
: "${MAYHEM_JOBS:=$(nproc)}"
: "${COVERAGE_FLAGS=}"
: "${SRC:=/mayhem}"
: "${ESPHOME_SRC:=/opt/toolchains/deps/esphome/src}"
: "${STANDALONE_FUZZ_MAIN:=/opt/mayhem/StandaloneFuzzTargetMain.c}"
export SANITIZER_FLAGS DEBUG_FLAGS CC CXX LIB_FUZZING_ENGINE MAYHEM_JOBS COVERAGE_FLAGS SRC ESPHOME_SRC

cd "$SRC"
[ -d "$ESPHOME_SRC/esphome/core" ] || { echo "ESPHome source missing at $ESPHOME_SRC" >&2; exit 1; }

OUT="$SRC/mayhem/out"
COMPONENTS="heltec_balancer_ble jk_balancer jk_balancer_modbus jk_bms jk_bms_ble jk_bms_display jk_modbus"

# Include tree: a symlink farm of ESPHome's esphome/ package with the generated config headers
# (mayhem/esphome_gen, what ESPHome's codegen writes for this config) in place of the source tree's
# dev-only ones, and this repo's components linked in as esphome/components/<c>. A farm (not -I order)
# because core headers include "defines.h" relative to their own directory.
rm -rf "$OUT/inc"
mkdir -p "$OUT/inc"
cp -rs "$ESPHOME_SRC/esphome" "$OUT/inc/esphome"
for g in defines.h version.h build_info_data.h; do
  ln -sfn "$SRC/mayhem/esphome_gen/esphome/core/$g" "$OUT/inc/esphome/core/$g"
done
for c in $COMPONENTS; do rm -rf "$OUT/inc/esphome/components/$c"; ln -s "$SRC/components/$c" "$OUT/inc/esphome/components/$c"; done

# The ESPHome host-platform sources script/cpp_unit_test.py compiles for these components' test config.
ESPHOME_SOURCES="
esphome/components/binary_sensor/automation.cpp esphome/components/binary_sensor/binary_sensor.cpp
esphome/components/binary_sensor/filter.cpp esphome/components/ble_client/automation.cpp
esphome/components/ble_client/ble_client.cpp esphome/components/ble_device_base/ble_aes_ccm.cpp
esphome/components/ble_device_base/ble_client_state.cpp esphome/components/ble_device_base/ble_device.cpp
esphome/components/ble_device_base/scan_response_merger.cpp esphome/components/button/button.cpp
esphome/components/esp32_ble/ble.cpp esphome/components/esp32_ble_client/ble_characteristic.cpp
esphome/components/esp32_ble_client/ble_client_base.cpp esphome/components/esp32_ble_client/ble_service.cpp
esphome/components/esp32_ble_tracker/bluedroid_stubs.cpp esphome/components/esp32_ble_tracker/esp32_ble_tracker.cpp
esphome/components/host/core.cpp esphome/components/host/gpio.cpp esphome/components/host/hal.cpp
esphome/components/host/helpers.cpp esphome/components/host/preferences.cpp
esphome/components/logger/logger.cpp esphome/components/logger/logger_host.cpp
esphome/components/logger/task_log_buffer_host.cpp esphome/components/mdns/mdns_component.cpp
esphome/components/mdns/mdns_host.cpp esphome/components/network/network_component.cpp
esphome/components/network/util.cpp esphome/components/number/automation.cpp
esphome/components/number/number_call.cpp esphome/components/number/number.cpp
esphome/components/number/number_traits.cpp esphome/components/select/select_call.cpp
esphome/components/select/select.cpp esphome/components/select/select_traits.cpp
esphome/components/sensor/filter.cpp esphome/components/sensor/sensor.cpp esphome/components/switch/switch.cpp
esphome/components/text_sensor/filter.cpp esphome/components/text_sensor/text_sensor.cpp
esphome/components/uart/uart_component.cpp esphome/components/uart/uart_component_host.cpp
esphome/components/uart/uart.cpp esphome/core/alloc_helpers.cpp esphome/core/application.cpp
esphome/core/color.cpp esphome/core/component.cpp esphome/core/component_iterator.cpp
esphome/core/entity_base.cpp esphome/core/gpio.cpp esphome/core/helpers.cpp esphome/core/log.cpp
esphome/core/scheduler.cpp esphome/core/time.cpp esphome/core/wake/wake_host.cpp"

# Upstream's flags for the host build (cpp_unit_test.py), minus its own -Og/-g3/sanitizer choice.
BASE_CXXFLAGS="-std=gnu++20 -DESPHOME_DEBUG -DESPHOME_LOG_LEVEL=ESPHOME_LOG_LEVEL_DEBUG -DUSE_HOST -fno-exceptions
 -Wno-sign-compare -Wno-unused-but-set-variable -Wno-unused-function -Wno-unused-variable -w
 -I$OUT/inc"
BASE_CXXFLAGS=$(echo $BASE_CXXFLAGS)  # one line: it is spliced into sh -c below

# compile_all <objdir> <flags...>: compiles ESPHome core + components + generated build info.
compile_all() {
  local objdir="$1"; shift
  local flags="$*"
  rm -rf "$objdir"; mkdir -p "$objdir"
  {
    for f in $ESPHOME_SOURCES; do echo "$OUT/inc/$f"; done
    for c in $COMPONENTS; do ls "$SRC/components/$c"/*.cpp; done
    echo "$SRC/mayhem/esphome_gen/esphome/core/build_info_data.cpp"
  } | while read -r f; do
    o="$objdir/$(echo "${f#/}" | tr '/' '_').o"
    extra=""
    # host/core.cpp holds ESPHome's main(); the fuzz build renames it so libFuzzer's main wins.
    case "$f" in */host/core.cpp) extra="$HOST_CORE_EXTRA";; esac
    printf '%s\0%s\0%s\0' "$f" "$o" "$extra"
  done | xargs -0 -n3 -P"$MAYHEM_JOBS" sh -c '$CXX '"$flags"' $2 -c "$0" -o "$1"'
  ar rcs "$objdir/libjkbms.a" "$objdir"/*.o
}

# 1) Fuzz build: everything instrumented with the sanitizers + DWARF 3.
# -fsanitize=fuzzer-no-link: SanCov on the project code itself (not only the harness TU), always.
FUZZ_FLAGS="$BASE_CXXFLAGS -O1 -fsanitize=fuzzer-no-link $SANITIZER_FLAGS $DEBUG_FLAGS"
HOST_CORE_EXTRA="-Dmain=esphome_host_main" compile_all "$OUT/fuzz" $FUZZ_FLAGS
export HOST_CORE_EXTRA=""

$CC $SANITIZER_FLAGS $DEBUG_FLAGS -c "$STANDALONE_FUZZ_MAIN" -o "$OUT/standalone_main.o"
$CXX $SANITIZER_FLAGS $DEBUG_FLAGS -c "$SRC/mayhem/lsan_off.cc" -o "$OUT/lsan_off.o"
for h in fuzz_jk_bms_ble fuzz_heltec_balancer_ble fuzz_jk_modbus fuzz_jk_balancer_modbus fuzz_jk_bms_display; do
  $CXX $FUZZ_FLAGS -c "$SRC/mayhem/harnesses/$h.cpp" -o "$OUT/$h.o"
  $CXX $SANITIZER_FLAGS $DEBUG_FLAGS $LIB_FUZZING_ENGINE "$OUT/$h.o" "$OUT/lsan_off.o" \
    "$OUT/fuzz/libjkbms.a" -lpthread -o "$SRC/$h"
  $CXX $SANITIZER_FLAGS $DEBUG_FLAGS "$OUT/standalone_main.o" "$OUT/$h.o" "$OUT/lsan_off.o" \
    "$OUT/fuzz/libjkbms.a" -lpthread -o "$SRC/$h-standalone"
done

# 2) Upstream's C++ unit suite (tests/components/*/*_test.cpp + the generated gtest main), normal flags.
TEST_FLAGS="$BASE_CXXFLAGS -O1 -g $COVERAGE_FLAGS"
compile_all "$OUT/test" $TEST_FLAGS
mkdir -p "$OUT/test-objs"; rm -f "$OUT/test-objs"/*.o
{ ls "$SRC"/tests/components/*/*_test.cpp; echo "$SRC/mayhem/esphome_gen/test_main.cpp"; } \
  | while read -r f; do printf '%s\0%s\0' "$f" "$OUT/test-objs/$(echo "${f#/}" | tr '/' '_').o"; done \
  | xargs -0 -n2 -P"$MAYHEM_JOBS" sh -c '$CXX '"$TEST_FLAGS"' -I'"$SRC"'/tests/components -I'"$SRC"'/mayhem/esphome_gen -c "$0" -o "$1"'
$CXX $COVERAGE_FLAGS "$OUT/test-objs"/*.o "$OUT/test/libjkbms.a" -lgtest -lpthread -o "$OUT/cpp_unit_tests"

ls -la "$SRC"/fuzz_* "$OUT/cpp_unit_tests"
