#include <gtest/gtest.h>

#include "esphome/components/logger/logger.h"
#include "esphome/core/application.h"
#include "esphome/core/helpers.h"
#include "esphome/core/preferences.h"

/*
This special main.cpp replaces the default one.
It will run all the Google Tests found in all compiled cpp files and then exit with the result
See README.md for more information
*/

// Auto generated code by esphome
// ========== AUTO GENERATED INCLUDE BLOCK BEGIN ===========
#include "esphome.h"
using namespace esphome;
alignas(logger::Logger) static unsigned char logger__logger_logger_id__pstorage[sizeof(logger::Logger)];
static logger::Logger *const logger_logger_id = reinterpret_cast<logger::Logger *>(logger__logger_logger_id__pstorage);
#ifndef __PICOLIBC__
using std::isnan;
#endif
using std::min;
using std::max;
#include <new>
using namespace binary_sensor;
alignas(mdns::MDNSComponent) static unsigned char mdns__mdns_mdnscomponent_id__pstorage[sizeof(mdns::MDNSComponent)];
static mdns::MDNSComponent *const mdns_mdnscomponent_id = reinterpret_cast<mdns::MDNSComponent *>(mdns__mdns_mdnscomponent_id__pstorage);
static constexpr size_t ESPHOME_LOOPING_COMPONENT_COUNT = \
  (1 * HasLoopOverride<logger::Logger>::value) + \
  (1 * HasLoopOverride<mdns::MDNSComponent>::value);
namespace esphome {
static Component *looping_components_storage[std::max<size_t>(ESPHOME_LOOPING_COMPONENT_COUNT, 1)];
}  // namespace esphome
#include "heltec_balancer_ble/frames_ek-24s4eb.h"
#include "heltec_balancer_ble/common.h"
#include "heltec_balancer_ble/frames_gw-24s4eb.h"
#include "heltec_balancer_ble/frames_ek-b24s8e200a.h"
#include "heltec_balancer_ble/frames_gw-24s4eb-zh123.h"
#include "heltec_balancer_ble/frames_ek-24s10eb.h"
#include "jk_balancer/common.h"
#include "jk_balancer_modbus/common.h"
#include "jk_bms/common.h"
#include "jk_bms_ble/frames_jk02_24s_v10.h"
#include "jk_bms_ble/common.h"
#include "jk_bms_ble/frames_jk04.h"
#include "jk_bms_ble/frames_jk02_32s_v11.h"
#include "jk_bms_ble/frames_logbook.h"
#include "jk_bms_ble/frames_jk04_b5a24s.h"
#include "jk_bms_ble/frames_jk02_32s_v15.h"
#include "jk_bms_ble/frames_jk02_32s_v19.h"
#include "jk_bms_ble/frames_jk02_32s_v14.h"
#include "jk_bms_display/common.h"
#include "jk_modbus/common.h"
namespace esphome {
static const char COMP_SRC_TABLE_STR_0[] PROGMEM = "logger";
static const char COMP_SRC_TABLE_STR_1[] PROGMEM = "mdns";
static const char *const COMP_SRC_TABLE[] PROGMEM = {COMP_SRC_TABLE_STR_0, COMP_SRC_TABLE_STR_1};
const LogString *component_source_lookup(uint8_t index) {
  if (index == 0 || index > 2) return LOG_STR("<unknown>");
  return reinterpret_cast<const LogString *>(
    progmem_read_ptr(&COMP_SRC_TABLE[index - 1]));
}
}  // namespace esphome
// ========== AUTO GENERATED INCLUDE BLOCK END ==========="

void original_setup() {
  // This function won't be run.

  // ========== AUTO GENERATED CODE BEGIN ===========
  // logger:
  //   baud_rate: 115200
  //   boot_log_buffer_size: 0
  //   boot_log_level: WARN
  //   boot_logs: {}
  //   deassert_rts_dtr: false
  //   id: logger_logger_id
  //   level: DEBUG
  //   logs: {}
  //   runtime_tag_levels: false
  //   tx_buffer_size: 512
  new(logger_logger_id) logger::Logger(115200);
  logger_logger_id->create_pthread_key();
  logger_logger_id->pre_setup();
  logger_logger_id->set_log_level(ESPHOME_LOG_LEVEL_DEBUG);
  // network:
  //   enable_ipv4: true
  //   enable_ipv6: false
  //   id: network_networkcomponent_id
  //   min_ipv6_addr_count: 0
  // esphome:
  //   areas: []
  //   build_flags:
  //     - -Og
  //     - -g3
  //     - -ggdb3
  //     - -DESPHOME_DEBUG
  //     - -fno-omit-frame-pointer
  //     - -fsanitize=address
  //     - -fsanitize=undefined
  //   build_path: build/cpptests-af6dd6baea60dcff
  //   debug_scheduler: false
  //   devices: []
  //   environment_variables: {}
  //   friendly_name: CPP Unit Tests
  //   friendly_name_separator: ' '
  //   includes:
  //     - /tmp/ejb/esphome/tests/components/main.cpp
  //     - /tmp/ejb/esphome/tests/components/heltec_balancer_ble
  //     - /tmp/ejb/esphome/tests/components/jk_balancer
  //     - /tmp/ejb/esphome/tests/components/jk_balancer_modbus
  //     - /tmp/ejb/esphome/tests/components/jk_bms
  //     - /tmp/ejb/esphome/tests/components/jk_bms_ble
  //     - /tmp/ejb/esphome/tests/components/jk_bms_display
  //     - /tmp/ejb/esphome/tests/components/jk_modbus
  //   includes_c: []
  //   libraries:
  //     - google/googletest@^1.15.2
  //   merge_warnings: true
  //   min_version: 2026.12.0-dev
  //   name: cpptests-af6dd6baea60dcff
  //   name_add_mac_suffix: false
  //   platformio_options: {}
  //   suspend_loop: false
  new (&App) Application;
  App.pre_setup("cpptests-af6dd6baea60dcff", 25, "CPP Unit Tests", 14);
  App.looping_components_.init(std::span<Component *>(looping_components_storage, ESPHOME_LOOPING_COMPONENT_COUNT));
  // binary_sensor:
  App.register_component_(logger_logger_id, 1);
  // mdns:
  //   disabled: false
  //   id: mdns_mdnscomponent_id
  //   services: []
  new(mdns_mdnscomponent_id) mdns::MDNSComponent();
  App.register_component_(mdns_mdnscomponent_id, 2);
  // host:
  //   mac_address: 98:35:69:AB:F6:79
  // ble_device_base:
  // sensor:
  // switch:
  // text_sensor:
  // =========== AUTO GENERATED CODE END ============
}

// The loop clock and current component one test moves must not leak into the next, like CORE.reset() in Python
class ResetAppListener : public ::testing::EmptyTestEventListener {
  void OnTestStart(const ::testing::TestInfo &) override {
    esphome::LoopBlockingGuard reset{nullptr, nullptr, 0};
    // Entities of the same kind share preference keys, so a value an earlier test saved would be restored
    if (esphome::global_preferences != nullptr)
      esphome::global_preferences->reset();
    this->high_frequency_at_start_ = esphome::HighFrequencyLoopRequester::is_high_frequency();
  }

  // Fail only the test that left the fast loop on, so a leak points at its culprit
  void OnTestEnd(const ::testing::TestInfo &info) override {
    if (!this->high_frequency_at_start_ && esphome::HighFrequencyLoopRequester::is_high_frequency()) {
      ADD_FAILURE() << info.test_suite_name() << "." << info.name()
                    << " left a HighFrequencyLoopRequester started; stop it before the test ends";
    }
  }

  bool high_frequency_at_start_{false};
};

void setup() {
  // Construct App once, as generated code does, before the logger, the listener or any test touches it.
  // A fixture that destroys App must construct it again before returning.
  // Placement new needs <new>, which the generated include block already provides
  new (&esphome::App) esphome::Application;

  // Log functions call global_logger->log_vprintf_() without a null check,
  // so we must set up a Logger before any test that triggers logging.
  static esphome::logger::Logger test_logger(0);
  test_logger.set_log_level(ESPHOME_LOG_LEVEL);
  test_logger.pre_setup();

  ::testing::InitGoogleTest();
  ::testing::UnitTest::GetInstance()->listeners().Append(new ResetAppListener);
  int exit_code = RUN_ALL_TESTS();
  // A test folder that never reached the build would otherwise pass as an empty run
  if (::testing::UnitTest::GetInstance()->total_test_count() == 0) {
    fprintf(stderr, "No tests were linked into this binary\n");
    exit_code = 1;
  }
  exit(exit_code);
}

void loop() {}
