/* rgp:protos */
#define RGP_SELF_HpGaugeGetSlotState_31e660 1
#include "port/game_protos.h"
#line 1
#include "types.h"
u8 HpGaugeGetSlotState_31e660(u8 *base, s32 i)
{
    if (i >= 0x10) i = 0xF;
    return *(u8 *)(i + (s32)base + 0x1C0);
}
