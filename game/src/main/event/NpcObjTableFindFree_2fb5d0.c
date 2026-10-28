/* rgp:protos */
#define RGP_SELF_NpcObjTableFindFree_2fb5d0 1
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
    u8 pad000[0x4];
    s32 m04;
    s16 m08;
};

struct Obj1 {
    u16 m00;
};

s32 NpcObjTableFindFree_2fb5d0(struct Obj0 *p0)
{
    s32 t0;
    s16 t1;
    struct Obj1 *l0;
    s32 l1;
    u16 t2;

    t0 = p0->m04;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m08;
    l0 = (struct Obj1 *)t0;
    l1 = 0;
    while (l1 < t1) {
        t2 = l0->m00;
        if ((t2 & 1) == 0) {
            return (s32)l0;
        }
        l0 = (struct Obj1 *)((u8 *)l0 + 0xE0);
        l1 = (l1 + 1);
    }
    return 0;
}
