#include "types.h"

extern void HpGaugeSetMode_31e2d0(void *, s32);
extern s32 HpGaugeSetFlags_31d3b0(void *, s32);
extern s32 HpGaugeClearSlots_31e9c0(void *);
extern void HpGaugeSetAlpha_31d1f0(void *, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x230];
    s32 m230;
    s32 m234;
    s32 m238;
    s32 m23C;
};

void HpGaugeReset_31e1e0(struct Obj0 *p0)
{
    s32 r1;
    s32 r2;

    HpGaugeSetMode_31e2d0(p0, 1);
    r1 = HpGaugeSetFlags_31d3b0(p0, 3);
    p0->m230 = 0;
    p0->m234 = 0;
    p0->m238 = 0;
    p0->m23C = 0x3F800000;
    r2 = HpGaugeClearSlots_31e9c0(p0);
    HpGaugeSetAlpha_31d1f0(p0, 1.0f);
}
