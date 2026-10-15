#include "types.h"

struct Obj {
    u8 pad[0x234];
    u8 lo : 2;
    u8 f : 1;
    u8 hi : 5;
};

extern "C" {
s32 CharaIsNearLeaderMaybe_1fb230(s32, s32);
void *GetGameData_1fede0(void);
void UiLayoutStringGlyphs_28a800(s32, s32, s32, s16, s32);
s32 MsgTableLookup_28aa30(s32, s32);
s32 UiEntryListFindByTag_28ea40(s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
s32 UiEntryListGetCurrentData_28ec60(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void UiSetWidgetParent_2911a0(s32, s32, s32);
s32 MenuGetOpenLeaderId_29acd0(void);
void MenuPartyCmdRowDim_29c390(s32, s32, s32);
void MenuPartyCmdListHighlight_29c440(s32, s32, s32, s32);
void MenuPartyWidgetToCursorCell_29f580(s32, s32, s32);
s8 *MenuGetCursorPos_29fae0(s32);
void MenuSetCursorPos_29faf0(s32, s32, s32);
void MenuWidgetFadeInOut_29fb00(s32, s32, s32, s32);
s32 CharaCountAbilitiesFilteredMaybe_3add30(s32, s32, s32, s32);
s32 CharaIsPartyMember_3ae110(s32);
s32 CharaIsPartyLeader_3ae1a0(s32);
s32 CharaCanBeLeader_3ae200(s32, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyGetSlotChara_3c2fb0(s32, s32);
extern u16 D_004614C0[];
extern f32 D_0047D6C8;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern s32 D_004823D8;
s32 MenuPartyMemberCmdOpenState_2b99f0(s32 arg0, s32 arg1);
}

s32 MenuPartyMemberCmdOpenState_2b99f0(s32 arg0, s32 arg1)
{
    s32 m;
    s32 id3;
    s32 e;
    s32 t;
    s32 g;
    s32 p;
    s32 h;
    s32 x;
    s32 k;
    s32 i;
    s32 o;
    bool ok;
    s8 *q;
    s32 id;
    s32 v;
    s32 id2;
    s32 j;
    s32 jj;
    s32 kk;

    if (arg1 != 0) {
        m = UiEntryListGetCurrentData_28ec60(D_00482364);
        i = 0;
        id = D_004614C0[*(s16 *)(m + 0x12)];
        do {
            UiSetWidgetsVisibleById_291110(D_00482360, (i + 0x11B) & 0xFFFF, 0, 1);
            i++;
        } while (i < 4);
        id2 = id & 0xFFFF;
        UiSetWidgetParent_2911a0(D_00482360, 0x183, id2);
        UiSetWidgetParent_2911a0(D_00482360, 0x118, id2);
        p = UiGetWidgetSprite_28fe10(D_00482360, id2, 0);
        if (*(s16 *)(m + 0x12) == 0) {
            k = 0;
            do {
                i = (k + 0x11B) & 0xFFFF;
                UiSetWidgetParent_2911a0(D_00482360, i, 0x11A);
                UiSetWidgetsVisibleById_291110(D_00482360, i, 1, 1);
                k++;
            } while (k < 4);
            UiSetWidgetPos_290f60(D_00482360, 0x11B, 0, 0xE);
            UiSetWidgetPos_290f60(D_00482360, 0x11D, 0, 0x29);
            UiSetWidgetPos_290f60(D_00482360, 0x11C, 0, 0x44);
            UiSetWidgetPos_290f60(D_00482360, 0x11E, 0, 0x5F);
            v = 0x7C;
            *(s16 *)(p + 0x64) = 0x8A;
            *(s16 *)(p + 0x44) = 0x8A;
            *(s16 *)(p + 0x24) = 0x8A;
            *(s16 *)(p + 0x4) = 0x8A;
            *(s16 *)(p + 0x144) = 0x7C;
            *(s16 *)(p + 0xA4) = 0x7C;
            *(s16 *)(p + 0x1C4) = 0x88;
            *(s16 *)(p + 0x1A4) = 0x88;
            *(s16 *)(p + 0x184) = 0x88;
            *(s16 *)(p + 0x160) = 0x88;
            *(s16 *)(p + 0xC0) = 0x88;
            *(s16 *)(p + 0x100) = 0x8D;
        } else {
            j = 0;
            do {
                if (j != 2) {
                    k = (j + 0x11B) & 0xFFFF;
                    UiSetWidgetParent_2911a0(D_00482360, k, 0x119);
                    UiSetWidgetsVisibleById_291110(D_00482360, k, 1, 1);
                }
                j++;
            } while (j < 4);
            UiSetWidgetPos_290f60(D_00482360, 0x11B, 0, 0xE);
            UiSetWidgetPos_290f60(D_00482360, 0x11C, 0, 0x29);
            UiSetWidgetPos_290f60(D_00482360, 0x11E, 0, 0x44);
            v = 0x54;
            *(s16 *)(p + 0x44) = 0x62;
            *(s16 *)(p + 0x24) = 0x62;
            *(s16 *)(p + 0x4) = 0x62;
            *(s16 *)(p + 0x124) = 0x54;
            *(s16 *)(p + 0x84) = 0x54;
            *(s16 *)(p + 0x184) = 0x60;
            *(s16 *)(p + 0x164) = 0x60;
            *(s16 *)(p + 0x140) = 0x60;
            *(s16 *)(p + 0xA0) = 0x60;
            *(s16 *)(p + 0xE0) = 0x65;
        }
        x = v / 2 + 0xB;
        UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(D_00482360, 0x11B, 0), MsgTableLookup_28aa30(D_004823D8, 0x898), 1, x, -2);
        UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(D_00482360, 0x11C, 0), MsgTableLookup_28aa30(D_004823D8, 0x89A), 1, x, -2);
        UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(D_00482360, 0x11E, 0), MsgTableLookup_28aa30(D_004823D8, 0x89B), 1, x, -2);
        UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(D_00482360, 0x11D, 0), MsgTableLookup_28aa30(D_004823D8, 0x899), 1, x, -2);
        UiSetWidgetPos_290f60(D_00482360, 0x183, 0x64, 0x22);
        id3 = id & 0xFFFFU;
        UiSetWidgetVisible_290010(D_00482360, id3, 1, -1);
        MenuWidgetFadeInOut_29fb00(D_00482370, id3, 1, 0);
        MenuPartyWidgetToCursorCell_29f580(D_00482370, id3, m);
        MenuSetCursorPos_29faf0(D_00482370, *(s16 *)(m + 0x10), *(s16 *)(m + 0x12));
        q = MenuGetCursorPos_29fae0(D_00482370);
        e = UiEntryListFindByTag_28ea40(D_00482364, 0x11);
        *(s16 *)(e + 0xE) = 3 - q[1];
        UiSetWidgetsVisibleById_291110(D_00482360, 0x183, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x183, *(s16 *)(e + 4), *(s16 *)(e + 6));
        UiFadeWidgetAlpha_290690(D_00482360, 0x183, 1.0f, D_0047D6C8, -1.0f);
        g = (s32)GetGameData_1fede0();
        o = PartyGetSlotChara_3c2fb0(*(s32 *)(g + 0x18), q[0] + q[1] * PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1));
        MenuPartyCmdListHighlight_29c440(D_00482370, id3, 0, 1);
        h = *(s32 *)(o + 0xC);
        k = MenuGetOpenLeaderId_29acd0();
        ok = true;
        if (!(*(u8 *)(*(s32 *)(g + 0x20) + 0x24C) & 1) && CharaIsNearLeaderMaybe_1fb230(h, k) == 0) {
            ok = false;
        }
        t = *(s32 *)(g + 0x18);
        if (PartyCountMembers_3c2010(t, 1, 1) + PartyCountReserve_3c1c20(t, 1, 1) == 1) {
            MenuPartyCmdRowDim_29c390(D_00482370, id2, 0);
        }
        if (PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1) == 1 && CharaIsPartyMember_3ae110(o) != 0) {
            MenuPartyCmdRowDim_29c390(D_00482370, id2, 0);
        }
        if (((Obj *)o)->f) {
            MenuPartyCmdRowDim_29c390(D_00482370, id2, 0);
        }
        if (q[1] == 0) {
            if (CharaIsPartyLeader_3ae1a0(o) != 0 || CharaCanBeLeader_3ae200(o, 0) == 0 || (*(u8 *)(o + 0x4B4) & 1) || CharaIsPartyMember_3ae110(o) == 0 || (*(u8 *)(*(s32 *)(g + 0x18) + 0x42D0) & 1) || !ok) {
                MenuPartyCmdRowDim_29c390(D_00482370, id2, 1);
            }
            if (PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1) == 1) {
                MenuPartyCmdRowDim_29c390(D_00482370, id2, 1);
            }
        }
        if (CharaCountAbilitiesFilteredMaybe_3add30(o, -1, -1, 0) == 0) {
            MenuPartyCmdRowDim_29c390(D_00482370, id2, (s16)(3 - q[1]));
        }
        StateMachineSetState_28ede0(D_0048235C, 0x4F, 0);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x11, 1);
    }
    return 1;
}
