#include "types.h"

typedef struct {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
    s16 x10;
    s16 x12;
    s16 x14;
    s16 x16;
    s16 x18;
    s16 x1A;
} Win34f;

u8 *GetGameData_1fede0(void);
s32 MsgTableLookup_28aa30(s32, s32);
void UiSlideInWidgetPair_28d010(s32, s32, s32);
void UiLayoutPanelFrame_28d580(Win34f *, s32, s32, s32, s32, s32);
Win34f *UiEntryListFindByTag_28ea40(s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
Win34f *UiEntryListGetCurrentData_28ec60(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetTextString_28f510(s32, s32, s32, s32);
void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
void UiSetSpriteScaleToSize_28fb10(s32, s32, s32, s32, s32);
void UiSetSpritePos_28fd10(s32, s32, s32, s32, s32);
Win34f *UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
s32 HelpBoardFillList_34dc90(s16);
f32 HelpBoardScrollBarLayout_34de40(s32, s32, s32);
s16 PartyMenuCursorGet_3c0760(s32, s32);
extern f32 D_0047D35C;
extern f32 D_0047D5EC;
extern f32 D_0047D638;
extern f32 D_0047D648;
extern s8 D_0047F6E8;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_004823D8;
extern s16 D_00482E86;
extern f32 D_00482E88;
extern f32 D_00482E8C;
extern f32 D_00482E90;
extern s32 D_00482EA0;
extern f32 D_00482EA4;
extern s16 D_00482EB4;
extern s8 D_00482EB8;

s32 HelpBoardListOpen_34f140(s32 arg0, s32 arg1)
{
    Win34f *w;
    Win34f *q;
    u8 *g;
    s32 a;
    s32 x;
    s32 t;
    s32 b;
    s32 n;
    f32 f;
    Win34f *r;

    if (arg1 != 0) {
        D_0047F6E8 = 1;
        w = UiGetWidgetSprite_28fe10(D_00482360, 0x212, 0);
        if (w != 0) {
            UiLayoutPanelFrame_28d580(w, 0, 0, 0x19D, 0x14F, 0);
        }
        UiSetSpriteSizeUvSize_28f670(D_00482360, 0x212, 0, 0, 0, 0, 0);
        UiSetSpriteScaleToSize_28fb10(D_00482360, 0x210, 0x17F, 0x12E, 0);
        UiSetSpriteScaleToSize_28fb10(D_00482360, 0x211, 0x17F, -9999, 0);
        UiSetWidgetVisible_290010(D_00482360, 0x20F, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0x20F, 0x200, 0x4B);
        UiMoveWidgetUniform_290f50(D_00482360, 0x20F, 0x5A, 0x4B, 0, D_0047D638);
        UiFadeWidgetAlpha_290690(D_00482360, 0x20F, 1.0f, 0.0625f, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x217, 1, 1);
        UiSetTextString_28f510(D_00482360, 0x214, MsgTableLookup_28aa30(D_004823D8, 0x1F41), 0);
        w = UiGetWidgetSprite_28fe10(D_00482360, 0x25, 0);
        if (w == 0) {
            return 0;
        }
        w->x0 = -4;
        w->x8 = 0xAC;
        w->xA = 0x68;
        w->xC = 0x54;
        w->x4 = 0x54;
        UiSlideInWidgetPair_28d010(0x1D, 0x14, D_00482360);
        UiFadeWidgetAlpha_290690(D_00482360, 0x41, 1.0f, D_0047D648, -1.0f);
        UiEntryListFindByTag_28ea40(D_00482364, 0x1E);
        D_00482E86 = 0;
        D_00482EA0 = 0;
        D_00482EA4 = 0.0f;
        UiEntryListSelectByTag_28ea90(D_00482364, 0x1E, 1);
        q = UiEntryListFindByTag_28ea40(D_00482364, 0x1E);
        g = GetGameData_1fede0();
        D_00482EB4 = 0;
        if (*(s16 *)(*(u8 **)(g + 0xC) + 0x26) == 1) {
            D_00482EB4 = PartyMenuCursorGet_3c0760(*(s32 *)(g + 0x18), 0x14);
        }
        x = *(volatile s16 *)&D_00482EB4;
        if (x >= 8) {
            a = 8;
        } else {
            a = x;
        }
        b = x - 8;
        if (b < 0) {
            b = 0;
        }
        q->x16 = a;
        q->x1A = b;
        n = HelpBoardFillList_34dc90(b);
        f = HelpBoardScrollBarLayout_34de40(0xF0, 9, n);
        D_00482E88 = f;
        UiSetWidgetPos_290f60(D_00482360, 0x21B, 0, (f32)q->x1A * f);
        r = UiEntryListGetCurrentData_28ec60(D_00482364);
        if (n < 10) {
            r->xA = n - 1;
            r->xE = n - 1;
        } else {
            r->xA = 8;
            r->xE = n - 1;
        }
        UiSetWidgetsVisibleById_291110(D_00482360, 0x219, 1, 1);
        if (n == 0) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x217, 0, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x219, 0, 1);
            UiSetWidgetAlpha_2907a0(D_00482360, 0x219, 0.0f);
        } else {
            UiSetWidgetAlpha_2907a0(D_00482360, 0x219, 1.0f);
        }
        UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, r->x2 + r->x12 * r->x6, 0);
        UiSetWidgetPos_290f60(D_00482360, 0x219, r->x0, r->x2 + r->x12 * r->x6);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x219, 0.0f);
        D_00482E8C = 0.5f;
        D_00482E90 = 1.0f;
    }
    if (D_00482EA0 == 0) {
        D_00482EA4 = D_00482EA4 + D_0047D5EC;
        if (!(D_00482EA4 < D_0047D35C)) {
            D_00482EA4 = D_0047D35C;
            D_00482EA0 = 1;
        }
    } else if (D_00482EA0 == 1) {
        D_00482EA4 -= D_0047D5EC;
    }
    UiSetWidgetColor_2905b0(D_00482360, 0x41, D_00482EA4, D_00482EA4, D_00482EA4, 1.0f);
    if (D_00482EA4 <= 1.0f && D_00482EA0 == 1) {
        D_00482EA4 = 1.0f;
        UiSetWidgetColor_2905b0(D_00482360, 0x41, 1.0f, 1.0f, 1.0f, 1.0f);
        D_00482EB8 = 0;
        StateMachineSetState_28ede0(D_0048235C, 0x83, 0);
    }
    return 1;
}
