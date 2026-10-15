#include "types.h"

extern s32 UiGetWidgetAbsPos_290fc0(s32, s32, void *, void *);
extern void * UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void * UiGetWidgetText_28f620(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483308;

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

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

struct Obj3 {
    s16 m00;
    s16 m02;
};

struct Obj3 *InsectCageMenuGetMarkerPos_389b80(s32 p0, s32 p1, struct Obj0 *p2, struct Obj2 *p3)
{
    s32 t0;
    s32 r0;
    s32 t1;
    struct Obj1 *r1;
    struct Obj1 * rv2;
    s32 rv3;
    s32 t2;
    s16 t3;
    s16 t4;
    s32 t5;
    s32 t6;
    s32 t7;
    struct Obj3 *r4;
    s32 rv5;
    s16 t8;
    s32 t9;
    s16 t10;
    s32 t11;
    s32 t12;
    s32 t13;
    s32 t14;

    t0 = D_00483308;
    r0 = UiGetWidgetAbsPos_290fc0(t0, ((p0 + 0x7580) & 0xFFFF), p2, p3);
    t1 = D_00483308;
    r1 = UiGetWidgetSprite_28fe10(t1, ((p0 + 0x7580) & 0xFFFF), 0);
    rv2 = (struct Obj1 *)r1;
    if (r1 != 0) {
        t2 = p2->m00;
        t3 = r1->m00;
        p2->m00 = (t2 - t3);
        t4 = r1->m02;
        t5 = p3->m00;
        p3->m00 = (t5 - t4);
        t6 = D_00483308;
        rv2 = (struct Obj1 *)(t5 - t4);
        rv3 = t6;
    } else {
        t7 = D_00483308;
        rv2 = (struct Obj1 *)r1;
        rv3 = t7;
    }
    r4 = UiGetWidgetText_28f620(rv3, ((p0 + 0x7580) & 0xFFFF), p1);
    if (r4 != 0) {
        t8 = r4->m00;
        t9 = p2->m00;
        p2->m00 = (t9 + t8);
        t10 = r4->m02;
        t11 = p3->m00;
        p3->m00 = (t11 + t10);
        t12 = p2->m00;
        rv5 = t12;
    } else {
        t13 = p2->m00;
        rv5 = t13;
    }
    p2->m00 = (rv5 + -0x1E);
    t14 = p3->m00;
    p3->m00 = (t14 + -2);
    return r4;
}
