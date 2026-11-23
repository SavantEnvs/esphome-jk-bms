// jk_bms_ble: BLE notification stream -> JkBmsBle::assemble() (frame reassembly, CRC, JK02/JK04 decoders).
// Input: byte 0 selects the protocol version (JK04 / JK02_24S / JK02_32S, as set from the YAML config),
// the rest is [len][payload] notify chunks (see fuzz_common.h).
#include "fuzz_common.h"
#include "attach_jk_bms_ble.h"
#include <memory>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzz::init_esphome();
  if (size < 1)
    return 0;
  using namespace esphome::jk_bms_ble;
  JkBmsBle bms;
  auto ents = std::make_unique<fuzz::JkBmsBleEntities>();
  ents->attach(bms);
  bms.set_throttle(0);  // decode every frame, not one per throttle window
  static const ProtocolVersion versions[] = {PROTOCOL_VERSION_JK04, PROTOCOL_VERSION_JK02_24S,
                                             PROTOCOL_VERSION_JK02_32S};
  bms.set_protocol_version(versions[data[0] % 3]);
  fuzz::feed_chunks(bms, data + 1, size - 1);
  return 0;
}
