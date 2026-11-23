// jk_balancer_modbus + jk_balancer: raw UART bytes -> JkBalancerModbus::loop() (0xEB 0x90 framing,
// checksum) -> JkBalancer::on_jk_balancer_modbus_data() (status decoder). Input: the wire bytes.
#include "fuzz_common.h"
#include "attach_jk_balancer.h"
#include <memory>
#include "esphome/components/jk_balancer_modbus/jk_balancer_modbus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzz::init_esphome();
  fuzz::FakeUart uart(data, size);
  esphome::jk_balancer_modbus::JkBalancerModbus bus;
  esphome::jk_balancer::JkBalancer bal;
  auto ents = std::make_unique<fuzz::JkBalancerEntities>();
  ents->attach(bal);
  bus.set_uart_parent(&uart);
  bal.set_parent(&bus);
  bal.set_address(0x01);
  bus.register_device(&bal);
  bus.loop();
  return 0;
}
