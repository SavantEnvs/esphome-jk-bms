// Auto-generated build_info data
#include "esphome/core/build_info_data.h"
#include "esphome/core/helpers.h"
#include "esphome/core/version.h"

namespace esphome {
const uint32_t ESPHOME_CONFIG_HASH = 0x8952f6fbU;  // NOLINT
// Folded at compile time, so the version string is not kept in RAM
static constexpr uint32_t CONFIG_VERSION_HASH = fnv1a_hash_extend(0x8952f6fbU, ESPHOME_VERSION);
const uint32_t ESPHOME_CONFIG_VERSION_HASH = CONFIG_VERSION_HASH;  // NOLINT
const time_t ESPHOME_BUILD_TIME = 1795454954;  // NOLINT
const size_t ESPHOME_COMMENT_SIZE = 1;  // NOLINT
#ifdef USE_ESP8266
const char ESPHOME_BUILD_TIME_STR[] PROGMEM = "2026-11-23 17:29:14 +0000";
const char ESPHOME_COMMENT_STR[] PROGMEM = "";
#else
const char ESPHOME_BUILD_TIME_STR[] = "2026-11-23 17:29:14 +0000";
const char ESPHOME_COMMENT_STR[] = "";
#endif
}  // namespace esphome
