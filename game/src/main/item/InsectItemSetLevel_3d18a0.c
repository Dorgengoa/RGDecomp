/* rgp:protos */
#define RGP_SELF_InsectItemSetLevel_3d18a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern struct { s32 v; s32 pad[3]; } D_00465D78;

s32 InsectItemSetLevel_3d18a0(u8 *o, s32 arg2)
{
    u8 *p;

    if (arg2 <= 0) {
        arg2 = 1;
    } else if (D_00465D78.v < arg2) {
        arg2 = D_00465D78.v;
    }
    p = *(u8 **)(o + 0x18);
    *(u8 *)(p + 0x27) = (u8)arg2;
    p = *(u8 **)(o + 0x18);
    return *(s8 *)(p + 0x27);
}
