/* rgp:protos */
#define RGP_SELF_InsectStatsCompact_384290 1
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
    s32 m00;
    s32 m04;
    u8 pad008[0x8];
    s32 m10;
    s32 m14;
};

struct Obj1 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

void InsectStatsCompact_384290(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 l0;
    s32 t4;

    t0 = p0->m00;
    p1->m00 = t0;
    t1 = p0->m04;
    p1->m04 = t1;
    t2 = p0->m10;
    p1->m08 = t2;
    t3 = p0->m14;
    p1->m0C = t3;
    l0 = 0;
    do {
        t4 = *(s32 *)((u8 *)p0 + (l0 << 2) + 0x18);
        *(s32 *)((u8 *)p1 + (l0 << 2) + 0x10) = t4;
        l0 = (l0 + 1);
    } while (l0 < 6);
}
