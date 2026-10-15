#include "types.h"

extern void * UiGetWidgetText_28f620(s32, s32, s32);
extern void TextStyleInitWithFontType_2931c0(void *, s32);
extern void FontMeasureString_26daf0(void *, s32, void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004DB150[];

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    s32 m00;
};

struct Obj2 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x2];
    s8 m0A;
};

struct Obj2 *UiGetWidgetTextSize_28f430(s32 p0, s32 p1, struct Obj0 *p2, struct Obj1 *p3, s32 p4)
{
    struct Obj2 *r0;
    s8 t0;
    s32 t1;

    p2->m00 = 0;
    p3->m00 = 0;
    r0 = UiGetWidgetText_28f620(p0, p1, p4);
    if (r0 != 0) {
        t0 = r0->m0A;
        TextStyleInitWithFontType_2931c0(D_004DB150, t0);
        t1 = r0->m04;
        FontMeasureString_26daf0(D_004DB150, t1, p2, p3);
    }
}
