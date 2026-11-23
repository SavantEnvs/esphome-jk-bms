// GENERATED from components/jk_bms_display/jk_bms_display.h: one entity per sensor/binary/text sensor, switch and
// number setter of JkBmsDisplay, so the decoders run their publish paths. Created fresh for every input.
#pragma once
#include "fuzz_entities.h"
#include "esphome/components/jk_bms_display/jk_bms_display.h"

namespace fuzz {
struct JkBmsDisplayEntities {
  esphome::binary_sensor::BinarySensor system_warning_binary_sensor_;
  esphome::binary_sensor::BinarySensor balancing_switch_binary_sensor_;
  esphome::binary_sensor::BinarySensor charging_binary_sensor_;
  esphome::binary_sensor::BinarySensor discharging_binary_sensor_;
  esphome::binary_sensor::BinarySensor overcurrent_protection_binary_sensor_;
  esphome::binary_sensor::BinarySensor short_circuit_protection_binary_sensor_;
  esphome::binary_sensor::BinarySensor cell_count_mismatch_binary_sensor_;
  esphome::sensor::Sensor total_voltage_sensor_;
  esphome::sensor::Sensor current_sensor_;
  esphome::sensor::Sensor power_sensor_;
  esphome::sensor::Sensor charging_power_sensor_;
  esphome::sensor::Sensor discharging_power_sensor_;
  esphome::sensor::Sensor min_cell_voltage_sensor_;
  esphome::sensor::Sensor max_cell_voltage_sensor_;
  esphome::sensor::Sensor min_voltage_cell_sensor_;
  esphome::sensor::Sensor max_voltage_cell_sensor_;
  esphome::sensor::Sensor state_of_charge_sensor_;
  esphome::sensor::Sensor delta_cell_voltage_sensor_;
  esphome::sensor::Sensor mosfet_temperature_sensor_;
  esphome::sensor::Sensor battery_temperature_sensor_;
  esphome::sensor::Sensor average_cell_voltage_sensor_;
  void attach(esphome::jk_bms_display::JkBmsDisplay &dev) {
    dev.set_system_warning_binary_sensor(&system_warning_binary_sensor_);
    dev.set_balancing_switch_binary_sensor(&balancing_switch_binary_sensor_);
    dev.set_charging_binary_sensor(&charging_binary_sensor_);
    dev.set_discharging_binary_sensor(&discharging_binary_sensor_);
    dev.set_overcurrent_protection_binary_sensor(&overcurrent_protection_binary_sensor_);
    dev.set_short_circuit_protection_binary_sensor(&short_circuit_protection_binary_sensor_);
    dev.set_cell_count_mismatch_binary_sensor(&cell_count_mismatch_binary_sensor_);
    dev.set_total_voltage_sensor(&total_voltage_sensor_);
    dev.set_current_sensor(&current_sensor_);
    dev.set_power_sensor(&power_sensor_);
    dev.set_charging_power_sensor(&charging_power_sensor_);
    dev.set_discharging_power_sensor(&discharging_power_sensor_);
    dev.set_min_cell_voltage_sensor(&min_cell_voltage_sensor_);
    dev.set_max_cell_voltage_sensor(&max_cell_voltage_sensor_);
    dev.set_min_voltage_cell_sensor(&min_voltage_cell_sensor_);
    dev.set_max_voltage_cell_sensor(&max_voltage_cell_sensor_);
    dev.set_state_of_charge_sensor(&state_of_charge_sensor_);
    dev.set_delta_cell_voltage_sensor(&delta_cell_voltage_sensor_);
    dev.set_mosfet_temperature_sensor(&mosfet_temperature_sensor_);
    dev.set_battery_temperature_sensor(&battery_temperature_sensor_);
    dev.set_average_cell_voltage_sensor(&average_cell_voltage_sensor_);
  }
};
}  // namespace fuzz
