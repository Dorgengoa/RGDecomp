#include "types.h"

extern s32 UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern s32 UiSetTextX_28f590(s32, s32, s32, s32);
extern void * UiGetWidgetSprite_28fe10(s32, s32, s32);
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

struct Obj0 {
    u8 pad000[0x4C4];
    s32 m4C4;
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
    s32 m08;
    u8 pad00C[0x8];
    s32 m14;
};

s32 MenuCharaAbilityInfoBoxSetup_29afe0(struct Obj0 *p0, struct Obj2 *p1, s32 p2, s32 p3, s32 p4, s32 p5, f32 fa0)
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
    s32 t6;
    s32 r5;
    s32 t7;
    s32 t8;
    s32 r6;
    s32 t9;
    s32 r7;
    s32 t10;
    s32 t11;
    s32 r9;
    s32 t12;

    t0 = p0->m4C4;
    r0 = UiSetSpriteX_28fcd0(t0, 0x231, -1, 0);
    t1 = p0->m4C4;
    r1 = UiSetSpriteX_28fcd0(t1, 0x230, -1, 0);
    t2 = p0->m4C4;
    r2 = UiSetTextX_28f590(t2, 0x230, -1, 0);
    t3 = p0->m4C4;
    r3 = UiSetSpriteX_28fcd0(t3, 0x232, -1, 0);
    t4 = p0->m4C4;
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
    if (p1 != 0) {
        t5 = p0->m4C4;
        t6 = p1->m08;
        r5 = UiSetTextString_28f510(t5, p2, t6, 0);
        t7 = p1->m14;
        t8 = p0->m4C4;
        r6 = UiSetTextString_28f510(t8, p2, t7, 1);
        t9 = p0->m4C4;
        r7 = UiSetWidgetPos_290f60(t9, p3, p4, p5);
        t10 = p0->m4C4;
        UiSetWidgetsVisibleById_291110(t10, p3, 1, 1);
        t11 = p0->m4C4;
        r9 = UiFadeWidgetAlpha_290690(t11, p3, 1.0f, fa0, -1.0f);
    } else {
        t12 = p0->m4C4;
        UiFadeWidgetAlpha_290690(t12, p3, 0.0f, -fa0, -1.0f);
    }
    return 1;
}
