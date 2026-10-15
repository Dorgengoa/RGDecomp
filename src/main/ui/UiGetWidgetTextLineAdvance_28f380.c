#include "types.h"

extern void * UiGetWidgetText_28f620(s32, s32, s32);
extern s32 TextStyleInitWithFontType_2931c0(void *, s32);
extern s32 FontGetLineAdvance_26f390(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004DB150[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xA];
    s8 m0A;
};

s32 UiGetWidgetTextLineAdvance_28f380(s32 p0, s32 p1, s32 p2)
{
    s32 v1C;
    struct Obj0 *r0;
    s32 rv3;
    s8 t0;
    s32 r1;
    s32 r2;
    s32 t1;

    r0 = UiGetWidgetText_28f620(p0, p1, p2);
    if (r0 == 0) {
        rv3 = 0;
    } else {
        t0 = r0->m0A;
        r1 = TextStyleInitWithFontType_2931c0(D_004DB150, t0);
        r2 = FontGetLineAdvance_26f390(D_004DB150, &v1C);
        t1 = v1C;
        rv3 = t1;
    }
    return rv3;
}
