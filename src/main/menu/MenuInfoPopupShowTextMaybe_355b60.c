#include "types.h"

extern s32 UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern s32 UiSetTextX_28f590(s32, s32, s32, s32);
extern void * UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void * UiGetWidgetText_28f620(s32, s32, s32);
extern s32 UiSetTextString_28f510(s32, s32, s32, s32);
extern s32 UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern s32 UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x5C];
    s32 m5C;
};

struct Obj1 {
    u8 pad000[0x2];
    s16 m02;
    u8 pad004[0x42];
    s16 m46;
    u8 pad048[0x1A];
    s16 m62;
    u8 pad064[0x22];
    s16 m86;
    u8 pad088[0x3E];
    s16 mC6;
    u8 pad0C8[0x1A];
    s16 mE2;
    u8 pad0E4[0x3E];
    s16 m122;
    u8 pad124[0x42];
    s16 m166;
    u8 pad168[0x1A];
    s16 m182;
};

struct Obj2 {
    u8 pad000[0x8];
    u16 m08;
};

struct Obj3 {
    u8 pad000[0x8];
    s32 m08;
    u8 pad00C[0x8];
    s32 m14;
};

s32 MenuInfoPopupShowTextMaybe_355b60(struct Obj0 *p0, struct Obj3 *p1, s32 p2, s32 p3, s32 p4, s32 p5, f32 fa0)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r1;
    s32 t2;
    s32 r2;
    s32 t3;
    s32 r3;
    s32 t4;
    struct Obj1 *r4;
    s32 t5;
    struct Obj2 *r5;
    u16 t6;
    s32 t7;
    s32 t8;
    s32 r6;
    s32 t9;
    s32 t10;
    s32 r7;
    s32 t11;
    s32 r8;
    s32 t12;
    s32 t13;
    s32 r10;
    s32 t14;

    t0 = p0->m5C;
    r0 = UiSetSpriteX_28fcd0(t0, 0x231, -1, 0);
    t1 = p0->m5C;
    r1 = UiSetSpriteX_28fcd0(t1, 0x230, -1, 0);
    t2 = p0->m5C;
    r2 = UiSetTextX_28f590(t2, 0x230, -1, 0);
    t3 = p0->m5C;
    r3 = UiSetSpriteX_28fcd0(t3, 0x232, -1, 0);
    t4 = p0->m5C;
    r4 = UiGetWidgetSprite_28fe10(t4, p3, 0);
    if (r4 == 0) {
        return 0;
    }
    r4->m166 = 0x4C;
    r4->mC6 = 0x4C;
    r4->m46 = 0x4C;
    r4->m182 = 0x5C;
    r4->m122 = 0x5C;
    r4->mE2 = 0x5C;
    r4->m62 = 0x5C;
    r4->m02 = 0x5C;
    r4->m86 = 0x65;
    t5 = p0->m5C;
    r5 = (struct Obj2 *)UiGetWidgetText_28f620(t5, p2, 1);
    t6 = r5->m08;
    r5->m08 = ((t6 & 0xFF80) | 3);
    if (p1 != 0) {
        t7 = p0->m5C;
        t8 = p1->m08;
        r6 = UiSetTextString_28f510(t7, p2, t8, 0);
        t9 = p1->m14;
        t10 = p0->m5C;
        r7 = UiSetTextString_28f510(t10, p2, t9, 1);
        t11 = p0->m5C;
        r8 = UiSetWidgetPos_290f60(t11, p3, p4, p5);
        t12 = p0->m5C;
        UiSetWidgetsVisibleById_291110(t12, p3, 1, 1);
        t13 = p0->m5C;
        r10 = UiFadeWidgetAlpha_290690(t13, p3, 1.0f, fa0, -1.0f);
    } else {
        t14 = p0->m5C;
        UiFadeWidgetAlpha_290690(t14, p3, 0.0f, -fa0, -1.0f);
    }
    return 1;
}
