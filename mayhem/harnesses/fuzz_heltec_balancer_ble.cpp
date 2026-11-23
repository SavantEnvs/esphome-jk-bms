// heltec_balancer_ble: BLE notification stream -> HeltecBalancerBle::assemble() (reassembly, length/CRC/EOF
// checks, cell info / settings / factory defaults / device info decoders).
// Input: byte 0 selects the protocol version (V1 / V2), the rest is [len][payload] notify chunks.
#include "fuzz_common.h"
#include "attach_heltec_balancer_ble.h"
#include <memory>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzz::init_esphome();
  if (size < 1)
    return 0;
  using namespace esphome::heltec_balancer_ble;
  HeltecBalancerBle bal;
  auto ents = std::make_unique<fuzz::HeltecBalancerBleEntities>();
  ents->attach(bal);
  bal.set_throttle(0);
  bal.set_protocol_version((data[0] & 1) ? PROTOCOL_VERSION_V2 : PROTOCOL_VERSION_V1);
  fuzz::feed_chunks(bal, data + 1, size - 1);
  return 0;
}
