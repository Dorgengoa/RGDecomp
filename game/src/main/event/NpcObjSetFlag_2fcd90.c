/* rgp:protos */
#define RGP_SELF_NpcObjSetFlag_2fcd90 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u16 m00;
};

u16 NpcObjSetFlag_2fcd90(struct Obj0 *p0, s32 p1, s32 p2)
{
    u16 rv0;
    u16 t0;
    u16 t1;
    u16 t2;

    rv0 = (t1 & (~(p1 & 0xFFFF) & 0xFFFF));
    if (p2 != 0) {
        t0 = p0->m00;
        p0->m00 = (t0 | p1);
        rv0 = (t0 | p1);
    } else {
        t1 = p0->m00;
        p0->m00 = (t1 & (~(p1 & 0xFFFF) & 0xFFFF));
        rv0 = (t1 & (~(p1 & 0xFFFF) & 0xFFFF));
    }
    t2 = p0->m00;
    return t2;
}
