#include "types.h"

typedef struct P433170 {
    void *m00;
    void *m04;
    u8 pad08[4];
    void *m0C;
    s32 m10;
    u8 pad14[4];
    f32 m18;
    u8 pad1C[0xC4];
    s16 mE0;
} P433170;

typedef struct R433170 {
    u8 pad00[4];
    s16 m04;
    s16 m06;
    s16 m08;
    s16 m0A;
    u8 pad0C[8];
    s16 m14;
    s16 m16;
} R433170;

extern s16 D_00480390;

extern void *MsgTableLookup_28aa30(void *o, s32 id);
extern void UiSetTextString_28f510(void *o, s32 id, void *a, s32 b);
extern void UiSetWidgetsVisibleById_291110(void *o, s32 id, s32 a, s32 b);
extern void UiSetWidgetAlpha_2907a0(void *o, s32 id, f32 t);
extern void UiFadeWidgetAlpha_290690(void *o, s32 id, f32 a, f32 b, f32 c);
extern void UiSetWidgetPos_290f60(void *o, s32 id, s32 x, s32 y);
extern R433170 *UiEntryListFindByTag_28ea40(void *o, s32 id);
extern void UiGetWidgetPos_2910a0(void *o, s32 id, s32 *a, s32 *b);
extern void UiSetSpriteU_28f930(void *o, s32 id, s32 a, s32 b);
extern f32 UiGetWidgetAlpha_290770(void *o, s32 id);
extern void TextEntrySetState_434410(void *p, s32 id, s32 a);

s32 TextEntryDialogFadeInState_433170(P433170 *p, s32 en)
{
    s16 t[5];
    s32 a;
    s32 b;
    R433170 *r;
    s16 *s;
    s16 *d;
    s32 i;

    if (en != 0) {
        p->m10 = 0;
        s = &D_00480390;
        d = t;
        i = 5;
        do {
            *d = *s;
            i--;
            s++;
            d++;
        } while (i > 0);
        UiSetTextString_28f510(p->m00, 0x11, MsgTableLookup_28aa30(p->m0C, t[p->mE0]), 0);
        UiSetTextString_28f510(p->m00, 0x11, MsgTableLookup_28aa30(p->m0C, 0x64), 1);
        UiSetTextString_28f510(p->m00, 0x11, MsgTableLookup_28aa30(p->m0C, 0x65), 2);
        UiSetWidgetsVisibleById_291110(p->m00, 0xF, 1, 1);
        UiSetWidgetAlpha_2907a0(p->m00, 0xF, 0.0f);
        UiFadeWidgetAlpha_290690(p->m00, 0xF, 1.0f, p->m18, -1.0f);
        UiSetWidgetPos_290f60(p->m00, 0xF, 0x4C, 0x92);
        r = UiEntryListFindByTag_28ea40(p->m04, 0x6D63);
        r->m14 = 1;
        UiGetWidgetPos_2910a0(p->m00, 0xF, &a, &b);
        UiSetWidgetPos_290f60(p->m00, 0x12, r->m04 + r->m14 * r->m08,
                     r->m06 + r->m16 * r->m0A);
        UiSetSpriteU_28f930(p->m00, 0x11, 0x7A - r->m14 * 52, 0);
        UiSetSpriteU_28f930(p->m00, 0x11, r->m14 * 52 + 0x46, 1);
    }
    if (UiGetWidgetAlpha_290770(p->m00, 0xF) >= 1.0f) {
        TextEntrySetState_434410(p, 0x6D68, 0);
    }
    return 1;
}
