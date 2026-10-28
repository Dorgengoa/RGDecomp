/* rgp:protos */
#define RGP_SELF_GameRecFindFreeInsectSlot_3ce390 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 m00;
};

struct Obj1 {
    u8 m00;
};

s32 GameRecFindFreeInsectSlot_3ce390(s32 p0)
{
    s32 l0;
    s32 l1;
    struct Obj0 *l2;
    u8 t0;
    s32 l3;
    struct Obj1 *l4;
    u8 t1;

    l2 = (struct Obj0 *)p0;
    l0 = 0;
    while (l0 < 0xF) {
        t0 = l2->m00;
        if ((t0 & 1) == 0) {
            return l0;
        }
        l0 = (l0 + 1);
        l1 = (t0 & 1);
        l2 = (struct Obj0 *)((u8 *)l2 + 0x34);
    }
    l3 = 0;
    l4 = (struct Obj1 *)p0;
    while (l3 < 0xF) {
        t1 = l4->m00;
        if ((((u64)(((s64)t1) << 0x3E)) >> 0x3F) != 0) {
            return l3;
        }
        l3 = (l3 + 1);
        l4 = (struct Obj1 *)((u8 *)l4 + 0x34);
    }
    return -1;
}
