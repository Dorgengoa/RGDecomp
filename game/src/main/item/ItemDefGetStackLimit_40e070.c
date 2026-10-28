/* rgp:protos */
#define RGP_SELF_ItemDefGetStackLimit_40e070 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern s32 D_00465B60;
struct Obj0 { u8 pad000[0x16]; u8 m16; u8 m17; };
s32 ItemDefGetStackLimit_40e070(struct Obj0 *p0)
{
    u8 t0;
    s32 t2;
    t0 = p0->m17;
    if ((((u64)(((s64)t0) << 0x39)) >> 0x3F) == 0) {
        return D_00465B60;
    }
    t2 = p0->m16 & 0x7F;
    if (t2 <= 0) {
        return D_00465B60;
    }
    return t2;
}
