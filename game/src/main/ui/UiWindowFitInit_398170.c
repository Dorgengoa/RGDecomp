/* rgp:protos */
#define RGP_SELF_UiWindowFitInit_398170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memset(void *, s32, s32);
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E95C0[];

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x18];
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s16 m30;
};

s32 UiWindowFitInit_398170(struct Obj0 *p0, s32 p1)
{
    s32 r1;
    s32 r2;

    memset(p0, 0, 0x34);
    r1 = ((s32)UiGetWidgetSprite_28fe10(D_004E95C0, p1, 0));
    p0->m00 = r1;
    r2 = ((s32)UiGetWidgetText_28f620(D_004E95C0, p1, 0));
    p0->m04 = r2;
    p0->m20 = 0;
    p0->m24 = 0;
    p0->m28 = 0x200;
    p0->m2C = 0x1C0;
    p0->m30 = 4;
    return r2;
}
