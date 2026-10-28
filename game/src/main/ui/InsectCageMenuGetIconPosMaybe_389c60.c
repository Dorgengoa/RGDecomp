/* rgp:protos */
#define RGP_SELF_InsectCageMenuGetIconPosMaybe_389c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483308;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    s16 m00;
    s16 m02;
};

struct Obj2 {
    s32 m00;
};

struct Obj1 *InsectCageMenuGetIconPosMaybe_389c60(s32 p0, s32 p1, struct Obj0 *p2, struct Obj2 *p3)
{
    s32 t0;
    s32 r0;
    s32 t1;
    struct Obj1 *r1;
    s32 rv2;
    s32 t2;
    s16 t3;
    s16 t4;
    s32 t5;
    s32 t6;
    s32 t7;
    s32 t8;

    t0 = D_00483308;
    r0 = ((s32)UiGetWidgetAbsPos_290fc0(t0, ((p0 + 0x7594) & 0xFFFF), p2, p3));
    t1 = D_00483308;
    r1 = UiGetWidgetSprite_28fe10(t1, ((p0 + 0x7594) & 0xFFFF), 0);
    if (r1 != 0) {
        t2 = p2->m00;
        t3 = r1->m00;
        p2->m00 = (t2 - t3);
        t4 = r1->m02;
        t5 = p3->m00;
        p3->m00 = (t5 - t4);
        t6 = p2->m00;
        rv2 = t6;
    } else {
        t7 = p2->m00;
        rv2 = t7;
    }
    p2->m00 = (rv2 + -0x91);
    t8 = p3->m00;
    p3->m00 = (t8 + -0x64);
    return r1;
}
