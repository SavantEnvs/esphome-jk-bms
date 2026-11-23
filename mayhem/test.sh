#!/usr/bin/env bash
# mayhem/test.sh — RUN upstream's C++ unit suite (tests/components/*/*_test.cpp, googletest; what upstream's
# run-cpp-tests.sh runs), built by mayhem/build.sh as mayhem/out/cpp_unit_tests. The tests assert decoded
# sensor values for known BMS/balancer frames, so a neutered decoder fails them.
set -uo pipefail
[ -n "${SOURCE_DATE_EPOCH:-}" ] || unset SOURCE_DATE_EPOCH
: "${MAYHEM_JOBS:=$(nproc)}"
: "${SRC:=/mayhem}"
cd "$SRC"

emit_ctrf() {
  local tool="$1" passed="$2" failed="$3" skipped="${4:-0}" pending="${5:-0}" other="${6:-0}"
  local tests=$(( passed + failed + skipped + pending + other ))
  cat > "${CTRF_REPORT:-$SRC/ctrf-report.json}" <<JSON
{
  "results": {
    "tool": { "name": "$tool" },
    "summary": {
      "tests": $tests,
      "passed": $passed,
      "failed": $failed,
      "pending": $pending,
      "skipped": $skipped,
      "other": $other
    }
  }
}
JSON
  printf 'CTRF {"results":{"tool":{"name":"%s"},"summary":{"tests":%d,"passed":%d,"failed":%d,"pending":%d,"skipped":%d,"other":%d}}}\n' \
    "$tool" "$tests" "$passed" "$failed" "$pending" "$skipped" "$other"
  [ "$failed" -eq 0 ]
}

RUNNER="$SRC/mayhem/out/cpp_unit_tests"
if [ ! -x "$RUNNER" ]; then
  echo "test runner $RUNNER missing — mayhem/build.sh should have built it" >&2
  emit_ctrf googletest 0 1
  exit 1
fi

# The expected test count is the number of TEST()/TEST_F() cases in the upstream sources, so a runner
# that runs fewer (or none) is a failure too.
expected=$(grep -hE '^\s*TEST(_F|_P)?\s*\(' tests/components/*/*_test.cpp | wc -l)
log=$(mktemp)
"$RUNNER" --gtest_brief=0 >"$log" 2>&1
rc=$?
tail -n 5 "$log"
passed=$(sed -n 's/^\[  PASSED  \] \([0-9]*\) test.*/\1/p' "$log" | tail -1)
failed=$(sed -n 's/^\[  FAILED  \] \([0-9]*\) test.*/\1/p' "$log" | tail -1)
skipped=$(sed -n 's/^\[  SKIPPED \] \([0-9]*\) test.*/\1/p' "$log" | tail -1)
passed=${passed:-0}; failed=${failed:-0}; skipped=${skipped:-0}
rm -f "$log"
missing=$(( expected - passed - failed - skipped ))
[ "$missing" -gt 0 ] || missing=0
if [ "$rc" -ne 0 ] && [ "$failed" -eq 0 ] && [ "$missing" -eq 0 ]; then failed=1; fi
echo "expected=$expected passed=$passed failed=$failed skipped=$skipped not-run=$missing rc=$rc"
emit_ctrf googletest "$passed" $(( failed + missing )) "$skipped"
