/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupToMsgId_4ef9f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EF9F0 -- map a factory job kind to its message id. */

s32 factory_FactoryPartGroupToMsgId_4ef9f0(void *o, u32 kind)
{
    switch (kind) {
    case 4:  return 0x4E20;
    case 5:  return 0x4E20;
    case 0:  return 0x4E21;
    case 3:  return 0x4E22;
    case 1:  return 0x4E23;
    case 2:  return 0x4E24;
    }
    return -1;
}
