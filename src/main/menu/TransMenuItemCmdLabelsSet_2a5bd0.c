#include "types.h"

typedef struct { s32 m0; } Obj;

extern s16 D_00450DD2[];
extern s32 D_00484770;

void UiSetWidgetAlpha_2907a0(s32, s32, f32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
s32 MsgTableLookup_28aa30(s32, s32);
void UiLayoutStringGlyphs_28a800(s32, s32, s32, s32, s32);

#define SET(h, id) UiLayoutStringGlyphs_28a800((h), MsgTableLookup_28aa30(D_00484770, (id)), 1, y, -2)

s32 TransMenuItemCmdLabelsSet_2a5bd0(Obj *obj, s32 idx, s32 mode)
{
    s32 y;
    s32 h1;
    s32 h2;
    s32 h3;
    s32 h4;
    s32 h5;
    s32 h6;

    y = (s16)(D_00450DD2[idx * 2] / 2 + 4);
    UiSetWidgetAlpha_2907a0(obj->m0, 0x7655, 1.0f);
    UiSetWidgetAlpha_2907a0(obj->m0, 0x7656, 1.0f);
    UiSetWidgetAlpha_2907a0(obj->m0, 0x7657, 1.0f);
    h1 = UiGetWidgetSprite_28fe10(obj->m0, 0x7652, 0);
    h2 = UiGetWidgetSprite_28fe10(obj->m0, 0x7653, 0);
    h3 = UiGetWidgetSprite_28fe10(obj->m0, 0x7654, 0);
    h4 = UiGetWidgetSprite_28fe10(obj->m0, 0x7655, 0);
    h5 = UiGetWidgetSprite_28fe10(obj->m0, 0x7656, 0);
    h6 = UiGetWidgetSprite_28fe10(obj->m0, 0x7657, 0);
    if (mode == 0) {
        SET(h1, 0x450);
    } else if (mode == 1) {
        SET(h1, 0x451);
    }
    if (idx == 0 || idx == 5) {
        SET(h2, 0x44F);
        SET(h3, 0x452);
        SET(h4, 0x44E);
        SET(h5, 0x44D);
        SET(h6, 0x457);
    } else if (idx == 1) {
        SET(h2, 0x44C);
        SET(h3, 0x44E);
        SET(h4, 0x44F);
        SET(h5, 0x457);
        UiSetWidgetAlpha_2907a0(obj->m0, 0x7657, 0.0f);
    } else if (idx == 3) {
        SET(h2, 0x453);
        SET(h3, 0x44F);
        SET(h4, 0x457);
        UiSetWidgetAlpha_2907a0(obj->m0, 0x7656, 0.0f);
        UiSetWidgetAlpha_2907a0(obj->m0, 0x7657, 0.0f);
    } else if (idx == 4) {
        SET(h2, 0x454);
        SET(h3, 0x455);
        SET(h4, 0x456);
        SET(h5, 0x44F);
        SET(h6, 0x457);
    }
    return 1;
}
