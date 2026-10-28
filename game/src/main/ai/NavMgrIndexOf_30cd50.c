/* rgp:protos */
#define RGP_SELF_NavMgrIndexOf_30cd50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

typedef struct Obj_FUN_0030cd50 {
    u8 *f00;
    s32 f04;
} Obj_FUN_0030cd50;

s32 NavMgrIndexOf_30cd50(Obj_FUN_0030cd50 *o, u8 *p)
{
    u8 *base;

    if (p == 0) {
        return -1;
    }
    base = o->f00;
    if (base == 0) {
        return -1;
    }
    if (p < base) {
        return -1;
    }
    if (base + o->f04 * 0x120 - 0x120 < p) {
        return -1;
    }
    return (p - base) / 0x120;
}
