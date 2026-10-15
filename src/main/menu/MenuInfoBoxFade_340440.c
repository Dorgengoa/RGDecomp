#include "types.h"

/* Two-sided transition setup.  beqz p1 falls into the long arm, so that is
   the source's if body and the short arm is the else.  The halfword block is
   written in retail's store order.  The tail is a 7-bit bitfield insert into
   the halfword at +0x8 (andi 0xFF80 / ori 3). */

struct S {
    u8 pad000[0x5C];
    s32 m5C;
};

struct P {
    u8 pad000[0x8];
    s32 m08;
    u8 pad00C[0x8];
    s32 m14;
};

extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern u8 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern u8 *UiGetWidgetText_28f620(s32, s32, s32);

s32 MenuInfoBoxFade_340440(struct S *p0, struct P *p1, s32 p2, s32 p3, s32 p4, s32 p5, f32 fp0)
{
    u8 *q;
    u8 *r;

    if (p1 != 0) {
        UiSetTextString_28f510(p0->m5C, p2, p1->m08, 0);
        UiSetTextString_28f510(p0->m5C, p2, p1->m14, 1);
        UiSetWidgetPos_290f60(p0->m5C, p3, p4, p5);
        UiFadeWidgetAlpha_290690(p0->m5C, p3, 1.0f, fp0, -1.0f);
        q = UiGetWidgetSprite_28fe10(p0->m5C, p3, 0);
        if (q == 0) {
            return 0;
        }
        *(s16 *)(q + 0x166) = 0x4C;
        *(s16 *)(q + 0xC6) = 0x4C;
        *(s16 *)(q + 0x46) = 0x4C;
        *(s16 *)(q + 0x182) = 0x5C;
        *(s16 *)(q + 0x122) = 0x5C;
        *(s16 *)(q + 0xE2) = 0x5C;
        *(s16 *)(q + 0x62) = 0x5C;
        *(s16 *)(q + 0x2) = 0x5C;
        *(s16 *)(q + 0x86) = 0x65;
        r = UiGetWidgetText_28f620(p0->m5C, p2, 1);
        *(u16 *)(r + 0x8) = (*(u16 *)(r + 0x8) & 0xFF80) | 3;
    } else {
        UiFadeWidgetAlpha_290690(p0->m5C, p3, 0.0f, -fp0, -1.0f);
    }
    return 1;
}
