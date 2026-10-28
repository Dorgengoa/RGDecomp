/* rgp:protos */
#define RGP_SELF_RowRangeLookup_428a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 RowRangeLookup_428a10(s32 p0, s32 p1, u8 *p2, s32 *p3, s32 *p4)
{
    s32 n;
    u8 *q;

    *p3 = -1;
    *p4 = -1;
    if (p1 > 0) {
        if (p2 != 0) {
            goto ok;
        }
    }
    return -1;
ok:
    n = *p2;
    if (n >= 0x14) {
        n = 0x14;
    }
    q = (u8 *)((n << 2) + p0);
    *p3 = *(s16 *)(q + 0x94);
    *p4 = *(s16 *)(q + 0x96);
    return *p3;
}
