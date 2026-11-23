// Shared scaffolding for the esphome-jk-bms fuzz harnesses (host platform build of ESPHome).
#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <new>
#include <vector>

#include "esphome/components/logger/logger.h"
#include "esphome/components/uart/uart_component.h"
#include "esphome/core/application.h"

// esphome/components/host/core.cpp defines main() (renamed by build.sh) and calls these.
void setup() {}
void loop() {}

namespace fuzz {

// ESPHOME_DEBUG asserts if anything logs before the logger exists: create it once, silenced.
// The logger is process-global but read-only after this (no input changes its level).
inline void init_esphome() {
  static bool done = false;
  if (done)
    return;
  done = true;
  new (&esphome::App) esphome::Application;
  static esphome::logger::Logger lg(0);
  lg.set_log_level(ESPHOME_LOG_LEVEL_NONE);
  lg.pre_setup();
}

// A UART whose RX side is the fuzz input; TX is discarded.
class FakeUart : public esphome::uart::UARTComponent {
 public:
  FakeUart(const uint8_t *data, size_t size) : rx_(data, data + size) {}
  void write_array(const uint8_t *, size_t) override {}
  bool peek_byte(uint8_t *data) override {
    if (pos_ >= rx_.size())
      return false;
    *data = rx_[pos_];
    return true;
  }
  bool read_array(uint8_t *data, size_t len) override {
    if (len > rx_.size() - pos_)
      return false;
    if (len)
      std::memcpy(data, rx_.data() + pos_, len);
    pos_ += len;
    return true;
  }
  size_t available() override { return rx_.size() - pos_; }
  esphome::uart::UARTFlushResult flush() override { return esphome::uart::UARTFlushResult::UART_FLUSH_RESULT_SUCCESS; }
#if defined(USE_ESP8266) || defined(USE_ESP32)
  void load_settings(bool) override {}
#endif

 protected:
  void check_logger_conflict() override {}

 private:
  std::vector<uint8_t> rx_;
  size_t pos_{0};
};

// Feed a BLE notification stream to a component's assemble(): the input after the first byte is a
// sequence of [len:u8][len bytes] chunks, one GATT notify payload each (a trailing short chunk is
// delivered truncated, like a cut-off notify).
template<typename T> void feed_chunks(T &dev, const uint8_t *data, size_t size) {
  size_t i = 0;
  while (i < size) {
    size_t len = data[i++];
    if (len > size - i)
      len = size - i;
    dev.assemble(data + i, static_cast<uint16_t>(len));
    i += len;
  }
}

}  // namespace fuzz
