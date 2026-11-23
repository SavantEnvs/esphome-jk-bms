// Minimal concrete ESPHome entities for the attach_*.h helpers (as in upstream's tests/components/*/common.h).
#pragma once
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/number/number.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace fuzz {
struct NullSwitch : esphome::switch_::Switch {
  void write_state(bool) override {}
};
struct NullNumber : esphome::number::Number {
  void control(float) override {}
};
}  // namespace fuzz
