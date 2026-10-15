#include "types.h"

typedef struct { s32 m0; } Obj;

extern s16 D_00450DD2[];
extern s32 D_004823D8;

void UiSetWidgetAlpha_2907a0(s32, s32, f32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
s32 MsgTableLookup_28aa30(s32, s32);
void UiLayoutStringGlyphs_28a800(s32, s32, s32, s32, s32);

#define SET(h, id) UiLayoutStringGlyphs_28a800((h), MsgTableLookup_28aa30(D_004823D8, (id)), 1, y, -2)

s32 MenuItemCmdLabelsSet_2a6060(Obj *obj, s32 idx)
{
    s32 y;
    s32 h1;
    s32 h2;
    s32 h3;
    s32 h4;
    s32 h5;
    s32 h6;

    y = (s16)(D_00450DD2[idx * 2] / 2 + 4);
    UiSetWidgetAlpha_2907a0(obj->m0, 0x86, 1.0f);
    UiSetWidgetAlpha_2907a0(obj->m0, 0x87, 1.0f);
    UiSetWidgetAlpha_2907a0(obj->m0, 0x88, 1.0f);
    h1 = UiGetWidgetSprite_28fe10(obj->m0, 0x83, 0);
    h2 = UiGetWidgetSprite_28fe10(obj->m0, 0x84, 0);
    h3 = UiGetWidgetSprite_28fe10(obj->m0, 0x85, 0);
    h4 = UiGetWidgetSprite_28fe10(obj->m0, 0x86, 0);
    h5 = UiGetWidgetSprite_28fe10(obj->m0, 0x87, 0);
    h6 = UiGetWidgetSprite_28fe10(obj->m0, 0x88, 0);
    if (idx == 0 || idx == 5) {
        if (idx == 0) {
            SET(h1, 0x4B0);
        } else {
            SET(h1, 0x4BC);
        }
        SET(h2, 0x4B4);
        SET(h3, 0x4B7);
        SET(h4, 0x4B3);
        SET(h5, 0x4B2);
        SET(h6, 0x4C2);
    } else if (idx == 1) {
        SET(h1, 0x4B1);
        SET(h2, 0x4BB);
        SET(h3, 0x4B3);
        SET(h4, 0x4B4);
        SET(h5, 0x4C2);
        UiSetWidgetAlpha_2907a0(obj->m0, 0x88, 0.0f);
    } else if (idx == 3) {
        SET(h1, 0x4BA);
        SET(h2, 0x4B9);
        SET(h3, 0x4B4);
        SET(h4, 0x4C2);
        UiSetWidgetAlpha_2907a0(obj->m0, 0x87, 0.0f);
        UiSetWidgetAlpha_2907a0(obj->m0, 0x88, 0.0f);
    } else if (idx == 2) {
        SET(h1, 0x4B8);
        SET(h2, 0x4B1);
        SET(h3, 0x4C0);
        UiSetWidgetAlpha_2907a0(obj->m0, 0x86, 0.0f);
        UiSetWidgetAlpha_2907a0(obj->m0, 0x87, 0.0f);
        UiSetWidgetAlpha_2907a0(obj->m0, 0x88, 0.0f);
    } else if (idx == 4) {
        SET(h1, 0x4BD);
        SET(h2, 0x4BE);
        SET(h3, 0x4BF);
        SET(h4, 0x4C1);
        SET(h5, 0x4B4);
        SET(h6, 0x4C2);
    }
    return 1;
}
