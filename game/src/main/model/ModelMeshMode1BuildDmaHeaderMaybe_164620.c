/* rgp:protos */
#define RGP_SELF_ModelMeshMode1BuildDmaHeaderMaybe_164620 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;
#pragma opt_propagation off

s32 ModelMeshMode1BuildDmaHeaderMaybe_164620(u8 *arg0, u8 *p)
{
    s32 n;
    u8 *q;

    *(s32 *)(p + 0x0) = 0x10000000;
    *(s32 *)(p + 0x4) = 0;
    *(s32 *)(p + 0x8) = 0x01000101;
    *(s32 *)(p + 0xC) = 0;
    n = 0x10;
    q = arg0 + 0xA0;
    *(s32 *)(p + 0x0) = (n / 16 - 1) | 0x10000000;
    *(u128 *)(p + 0x10) = 0;
    *(s32 *)(p + 0x10) = 0x60000000;
    *(s32 *)(p + 0x18) = 0x11000000;
    n = 0x20;
    *(u8 **)(q + 0x20) = p;
    return n / 16;
}
