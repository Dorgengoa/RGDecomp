#include "types.h"

extern void TextStyleSetOutlineMode_26f160(void *, s32);
extern void TextStyleSetGradientMode_26e330(void *, s32);
extern void TextStyleSetFixedPitch_26f140(void *, s32);
extern void TextStyleSetZEnable_26e420(void *, s32);
extern void TextStyleSetZ_26e440(void *, s32);
extern void TextStyleSetRgba_26f280(void *, s32, s32, s32, s32);
extern void TextStyleSetGradRgba_26f1e0(void *, s32, s32, s32, s32);
extern void TextStyleSetAlpha_26dd40(void *, s32);
extern void TextStyleSetSpacing_26f300(void *, s32, s32);
extern void TextStyleSetSpaceWidth_26f5e0(void *, s32);
extern void TextStyleSetFontType_26edf0(void *, s32);
extern void TextStyleClearClipRect_26f600(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    u8 m18;
    u8 pad019[0x23];
    s16 m3C;
};

void TextStyleInit_26c610(struct Obj0 *p0)
{
    TextStyleSetOutlineMode_26f160(p0, 1);
    TextStyleSetGradientMode_26e330(p0, 0);
    TextStyleSetFixedPitch_26f140(p0, 0);
    TextStyleSetZEnable_26e420(p0, 0);
    TextStyleSetZ_26e440(p0, 0);
    TextStyleSetRgba_26f280(p0, 0x80, 0x80, 0x80, 0x80);
    TextStyleSetGradRgba_26f1e0(p0, 0x80, 0x80, 0x80, 0x80);
    p0->m18 = 0;
    TextStyleSetAlpha_26dd40(p0, 0x80);
    TextStyleSetSpacing_26f300(p0, -3, 2);
    TextStyleSetSpaceWidth_26f5e0(p0, 7);
    TextStyleSetFontType_26edf0(p0, 1);
    TextStyleClearClipRect_26f600(p0);
    p0->m3C = 0;
}
