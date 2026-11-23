// GENERATED from components/jk_balancer/jk_balancer.h: one entity per sensor/binary/text sensor, switch and
// number setter of JkBalancer, so the decoders run their publish paths. Created fresh for every input.
#pragma once
#include "fuzz_entities.h"
#include "esphome/components/jk_balancer/jk_balancer.h"

namespace fuzz {
struct JkBalancerEntities {
  esphome::binary_sensor::BinarySensor balancing_binary_sensor_;
  esphome::binary_sensor::BinarySensor online_status_binary_sensor_;
  fuzz::NullNumber cell_count_number_;
  fuzz::NullNumber balance_trigger_voltage_number_;
  fuzz::NullNumber max_balance_current_number_;
  esphome::sensor::Sensor min_cell_voltage_sensor_;
  esphome::sensor::Sensor max_cell_voltage_sensor_;
  esphome::sensor::Sensor min_voltage_cell_sensor_;
  esphome::sensor::Sensor max_voltage_cell_sensor_;
  esphome::sensor::Sensor delta_cell_voltage_sensor_;
  esphome::sensor::Sensor average_cell_voltage_sensor_;
  esphome::sensor::Sensor battery_temperature_sensor_;
  esphome::sensor::Sensor total_voltage_sensor_;
  esphome::sensor::Sensor cell_count_detected_sensor_;
  esphome::sensor::Sensor errors_bitmask_sensor_;
  esphome::sensor::Sensor balancer_status_sensor_;
  esphome::sensor::Sensor balancing_current_sensor_;
  fuzz::NullSwitch balancer_switch_;
  esphome::text_sensor::TextSensor errors_text_sensor_;
  void attach(esphome::jk_balancer::JkBalancer &dev) {
    dev.set_balancing_binary_sensor(&balancing_binary_sensor_);
    dev.set_online_status_binary_sensor(&online_status_binary_sensor_);
    dev.set_cell_count_number(&cell_count_number_);
    dev.set_balance_trigger_voltage_number(&balance_trigger_voltage_number_);
    dev.set_max_balance_current_number(&max_balance_current_number_);
    dev.set_min_cell_voltage_sensor(&min_cell_voltage_sensor_);
    dev.set_max_cell_voltage_sensor(&max_cell_voltage_sensor_);
    dev.set_min_voltage_cell_sensor(&min_voltage_cell_sensor_);
    dev.set_max_voltage_cell_sensor(&max_voltage_cell_sensor_);
    dev.set_delta_cell_voltage_sensor(&delta_cell_voltage_sensor_);
    dev.set_average_cell_voltage_sensor(&average_cell_voltage_sensor_);
    dev.set_battery_temperature_sensor(&battery_temperature_sensor_);
    dev.set_total_voltage_sensor(&total_voltage_sensor_);
    dev.set_cell_count_detected_sensor(&cell_count_detected_sensor_);
    dev.set_errors_bitmask_sensor(&errors_bitmask_sensor_);
    dev.set_balancer_status_sensor(&balancer_status_sensor_);
    dev.set_balancing_current_sensor(&balancing_current_sensor_);
    dev.set_balancer_switch(&balancer_switch_);
    dev.set_errors_text_sensor(&errors_text_sensor_);
  }
};
}  // namespace fuzz
