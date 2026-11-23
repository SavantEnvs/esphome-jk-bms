// jk_bms_display: raw UART bytes from the display port -> JkBmsDisplay::loop() (0xA5 0x5A framing,
// status / raw data decoders). Input: the wire bytes.
#include "fuzz_common.h"
#include "attach_jk_bms_display.h"
#include <memory>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzz::init_esphome();
  fuzz::FakeUart uart(data, size);
  esphome::jk_bms_display::JkBmsDisplay disp;
  auto ents = std::make_unique<fuzz::JkBmsDisplayEntities>();
  ents->attach(disp);
  disp.set_uart_parent(&uart);
  disp.loop();
  return 0;
}
