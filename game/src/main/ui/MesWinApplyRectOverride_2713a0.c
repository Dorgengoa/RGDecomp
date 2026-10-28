/* rgp:protos */
#define RGP_SELF_MesWinApplyRectOverride_2713a0 1
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
    u8 pad000[0xA0];
    s32 mA0;
    s32 mA4;
    s32 mA8;
    s32 mAC;
};

struct Obj1 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

void MesWinApplyRectOverride_2713a0(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;
    s32 rv0;
    s32 t1;
    s32 t2;
    s32 rv1;
    s32 t3;
    s32 t4;
    s32 rv2;
    s32 t5;
    s32 t6;

    t0 = p0->mA0;
    if (t0 > -1) {
        p1->m00 = t0;
        t1 = p0->mA4;
        rv0 = t1;
    } else {
        t2 = p0->mA4;
        rv0 = t2;
    }
    if (rv0 > -1) {
        p1->m04 = rv0;
        t3 = p0->mA8;
        rv1 = t3;
    } else {
        t4 = p0->mA8;
        rv1 = t4;
    }
    if (rv1 > 0) {
        p1->m08 = rv1;
        t5 = p0->mAC;
        rv2 = t5;
    } else {
        t6 = p0->mAC;
        rv2 = t6;
    }
    if (rv2 > 0) {
        p1->m0C = rv2;
        return;
    }
}
