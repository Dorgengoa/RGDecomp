/* rgp:protos */
#line 1
#include "types.h"

struct Sel2b7 {
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
};

extern "C" {
u8 *GetGameData_1fede0(void);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
void MenuGetSwapPair_29f970(s32, s32 *, s32 *);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void MenuPartyCursorClampMaybe_2ba420(Sel2b7 *);
s32 PadIsTriggered_1839f0(void *, s32);
void UiSelFrameSetRect_28db40(void *, s32, s16, s16, s16, s16, s32, s32);
void UiSelFrameCalcTileCounts_28d9d0(void *);
u8 *UiFindWidget_290460(s32, s32);
void MenuPartyPanelIconSizesResetMaybe_29ddf0(s32);
s32 GetMenuResGroup_206a40(void);
s32 ResGroupListFindValueById_42c3a0(s32, s32);
void MenuLayoutPartyPanelMaybe_29cfb0(s32, s32, s32, s32);
void MenuLayoutPartyFramesMaybe_29cb70(s32, s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, u16, f32, f32, f32, f32);
void MenuSetPartyEquipIcon_29ec60(s32, s32, s32, s32);
void MenuPartyCharaIconsLayoutMaybe_29ad30(s32, s32, s16);
void MenuShowCharaStats_29bb00(s32, s32);
extern s16 D_004510E0[];
extern s16 D_004510E2[];
extern s16 D_004510E4[];
extern s16 D_004510E6[];
extern f32 D_0047D460;
extern s32 D_00482360;
extern s32 D_00482370;
extern s16 D_0048253E;
extern s16 D_0048256C;
extern s16 D_00482570;
extern u8 D_004B2570[];
extern u8 D_004DB730[];
}

extern "C" s32 MenuPartySwapCursorUpdateCbMaybe_2b7b50(Sel2b7 *self)
{
    u8 *g;
    s32 n1;
    s32 n2;
    s32 cur;
    s32 dummy;
    s32 idx;
    s32 page;
    s32 sel;
    s32 t;
    s32 dir;
    bool up;
    bool down;
    s16 k;
    u8 *w;
    s32 pos;

    g = GetGameData_1fede0();
    n1 = PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1);
    n2 = PartyCountReserve_3c1c20(*(s32 *)(g + 0x18), 1, 1);
    MenuGetSwapPair_29f970(D_00482370, &cur, &dummy);
    page = cur >= n1;
    idx = (cur >= n1) ? cur - n1 : cur;
    if (D_0048253E != self->x12) {
        if (self->x12 == 0) {
            self->x8 = n1 - 1;
            self->x0 = 0xD0;
            self->x2 = 0xBE;
            self->x4 = 0x82;
            if (page == 0) {
                if (idx == 0 || idx == self->x8) {
                    self->x8--;
                }
                if (idx == 0) {
                    self->x0 += self->x4;
                }
            }
            UiFadeWidgetAlpha_290690(D_00482360, 0x14B, 1.0f, D_0047D460, 0.0f);
        } else if (n2 > 0) {
            self->x8 = n2 - 1;
            self->x0 = 0x8F;
            self->x2 = 0x196;
            self->x4 = 0x50;
            if (page == 1) {
                if (idx == 0 || idx == self->x8) {
                    self->x8--;
                }
                if (idx == 0) {
                    self->x0 += self->x4;
                }
            }
            UiFadeWidgetAlpha_290690(D_00482360, 0x14B, 1.0f, D_0047D460, 0.0f);
        } else {
            self->x12 = 0;
        }
    }
    t = page == self->x12;
    if (t) {
        t = idx == 0;
    }
    sel = t & 0xFF;
    MenuPartyCursorClampMaybe_2ba420(self);
    if (cur == sel + self->x10 + self->x12 * n1) {
        if (self->x10 < D_0048256C) {
            dir = -1;
        } else {
            dir = 1;
        }
        if (D_0048253E != self->x12 && (self->x10 + dir < 0 || self->x8 < self->x10 + dir)) {
            if (self->x10 == 4 && self->x12 == 1) {
                self->x10 = 3;
            } else {
                self->x10 = D_0048256C;
            }
        } else {
            up = false;
            down = false;
            if (PadIsTriggered_1839f0(D_004B2570, 0x8004) != 0) {
                up = true;
            } else if (PadIsTriggered_1839f0(D_004B2570, 0x2008) != 0) {
                down = true;
            }
            if (up && self->x10 + dir < 0) {
                self->x10 = self->x8;
            } else if (up && self->x10 == self->x8) {
                self->x10 = self->x8 - 1;
            } else if (down && self->x10 + dir > self->x8) {
                self->x10 = 0;
            } else if (down && self->x10 == 0) {
                self->x10 = 1;
            } else {
                self->x10 += (s16)dir;
            }
        }
    }
    if (self->x10 < 0) {
        self->x10 = 0;
    } else if (self->x8 < self->x10) {
        self->x10 = self->x8;
    }
    k = D_00482570 = sel + self->x10 + self->x12 * 3;
    UiSelFrameSetRect_28db40(D_004DB730, 0x14B, D_004510E0[k * 4], D_004510E2[k * 4], D_004510E4[k * 4], D_004510E6[k * 4], 0x42, 0x42);
    UiSelFrameCalcTileCounts_28d9d0(D_004DB730);
    w = UiFindWidget_290460(D_00482360, 0xD7);
    if (w != 0) {
        MenuPartyPanelIconSizesResetMaybe_29ddf0(D_00482370);
        *(s32 *)(w + 0x20) = ResGroupListFindValueById_42c3a0(GetMenuResGroup_206a40(), self->x12 + 0x3A2);
    }
    MenuLayoutPartyPanelMaybe_29cfb0(D_00482370, 0xD7, sel + self->x10, self->x12);
    MenuLayoutPartyFramesMaybe_29cb70(D_00482370, 0xB8, sel + self->x10, self->x12);
    UiSetWidgetColor_2905b0(D_00482360, D_00482570 + 0xDF, 1.0f, 1.0f, 1.0f, 1.0f);
    pos = sel + self->x10 + self->x12 * n1;
    MenuSetPartyEquipIcon_29ec60(D_00482370, pos, 0x113, 0);
    MenuSetPartyEquipIcon_29ec60(D_00482370, pos, 0x114, 1);
    MenuSetPartyEquipIcon_29ec60(D_00482370, pos, 0x115, 2);
    MenuSetPartyEquipIcon_29ec60(D_00482370, pos, 0x116, 3);
    MenuPartyCharaIconsLayoutMaybe_29ad30(D_00482370, 0xDB, pos);
    MenuShowCharaStats_29bb00(D_00482370, pos);
    D_0048256C = self->x10;
    D_0048253E = self->x12;
    return 1;
}
