// jk_modbus + jk_bms: raw UART bytes -> JkModbus::loop() (header/length/checksum framing) ->
// JkBms::on_jk_modbus_data() (status frame decoder). Input: the bytes the BMS sends on the wire.
#include "fuzz_common.h"
#include "attach_jk_bms.h"
#include <memory>
#include "esphome/components/jk_modbus/jk_modbus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzz::init_esphome();
  fuzz::FakeUart uart(data, size);
  esphome::jk_modbus::JkModbus bus;
  esphome::jk_bms::JkBms bms;
  auto ents = std::make_unique<fuzz::JkBmsEntities>();
  ents->attach(bms);
  bus.set_uart_parent(&uart);
  bms.set_parent(&bus);
  bms.set_address(0x4E);  // the frame's first header byte doubles as the dispatch address
  bus.register_device(&bms);
  bus.loop();
  return 0;
}
