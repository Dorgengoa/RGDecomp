#pragma optimization_level 3
#pragma opt_propagation off
#pragma opt_common_subs off
#pragma opt_loop_invariants off
#include "types.h"

typedef struct {
    f32 v;
} Int;

extern s32 GetGameData_1fede0(void);
extern s32 GetMenuResGroup_206a40(void);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 UiFindWidget_290460(s32, s32);
extern void UiFadeWidgetColor_2904e0(s32, s32, f32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuPartyReserveSlotLayoutMaybe_29c680(s32, s32);
extern void MenuLayoutPartyFramesMaybe_29cb70(s32, s32, s32, s32);
extern void MenuLayoutPartyPanelMaybe_29cfb0(s32, s32, s32, s32, s32);
extern void MenuPartyPanelIconSizesResetMaybe_29ddf0(s32, s32);
extern void MenuPartyReserveGaugesRefresh_29e4e0(s32, s32);
extern void MenuPartyReserveFaceSprites_29ea50(s32, s32);
extern void MenuSetPartyEquipIcon_29ec60(s32, s32, s32, s32);
extern void MenuPartyMemberStatValues_29edc0(s32, s32);
extern void MenuPartyMemberGaugesRefresh_29f000(s32, s32);
extern void MenuPartyMemberLabelSpritesMaybe_29f370(s32, s32);
extern void MenuPartyMemberFaceSprites_29f7f0(s32, s32);
extern void MenuGetSwapPair_29f970(s32, s32 *, s32 *);
extern void MenuSetCharaSel_29fa20(s32, s32);
extern s32 MenuGetCharaSel_29fa30(s32);
extern void MenuSetCursorPos_29faf0(s32, s32, s32);
extern s32 CharaCanBeLeader_3ae200(s32, s32);
extern void PartySwapMembers_3c0ad0(s32, s32, s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyGetMemberChara_3c2420(s32, s32);
extern void PartySetLeaderId_3c27c0(s32, s32);
extern s32 PartyGetSlotChara_3c2fb0(s32, s32);
extern s32 PartyGetSlotId_3c3120(s32, s32);
extern s32 ResGroupListFindValueById_42c3a0(s32, s32);
extern f32 D_0047D288;
extern f32 D_0047D35C;
extern f32 D_0047D6B4;
extern f32 D_0047D6BC;
extern f32 D_0047D6C0;
extern s16 D_0047ECF0[4];
extern f32 D_0047ED38;
extern f32 D_0047ED3C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482370;

s32 MenuPartySwapApplyState_2b8120(s32 pad0, s32 arg1) {
    s32 wrap;
    s32 ta;
    s32 v;
    s32 a;
    s32 ch;
    s32 x;
    s32 b;
    f32 f;
    s32 n;
    s32 i;
    s32 p[2];
    s32 gm;
    s32 obj;
    s32 cur;
    s32 t;
    s32 tb;
    s32 y;

    *(f32 *)&p[0] = D_0047ED38;
    *(f32 *)&p[1] = D_0047ED3C;
    MenuGetSwapPair_29f970(D_00482370, &p[0], &p[1]);
    gm = GetGameData_1fede0();
    {
        s32 one = 1;
        n = PartyCountMembers_3c2010(*(s32 *)(gm + 0x18), one, one);
    }
    x = p[0];
    wrap = x >= n;
    if (x >= n) {
        cur = x - n;
    } else {
        cur = x;
    }
    y = p[1];
    if (arg1 != 0) {
        a = PartyGetSlotChara_3c2fb0(*(s32 *)(gm + 0x18), p[0]);
        b = PartyGetSlotChara_3c2fb0(*(s32 *)(gm + 0x18), p[1]);
        { s32 bc = *(s32 *)(b + 0xC); s32 ac = *(s32 *)(a + 0xC); PartySwapMembers_3c0ad0(*(s32 *)(gm + 0x18), ac, bc, 0, 0); }
        MenuPartyMemberLabelSpritesMaybe_29f370(D_00482370, 0xF8);
        MenuPartyMemberFaceSprites_29f7f0(D_00482370, 0xF5);
        MenuPartyMemberGaugesRefresh_29f000(D_00482370, 0xEF);
        MenuPartyMemberStatValues_29edc0(D_00482370, 0xEC);
        MenuPartyReserveFaceSprites_29ea50(D_00482370, 0xFB);
        MenuPartyReserveSlotLayoutMaybe_29c680(D_00482370, 0x104);
        MenuPartyReserveGaugesRefresh_29e4e0(D_00482370, 0x105);
        UiFadeWidgetAlpha_290690(D_00482360, 0x184, 0.0f, D_0047D6BC, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x14B, 0.0f, D_0047D6BC, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x14C, 0.0f, D_0047D6BC, -1.0f);
        tb = (u16)(p[1] + 0xDF);
        {
            f32 d = D_0047D35C;
            UiFadeWidgetColor_2904e0(D_00482360, (u16)(p[0] + 0xDF), d, d, d, d, D_0047D6B4);
        }
        {
            f32 d = D_0047D35C;
            UiFadeWidgetColor_2904e0(D_00482360, tb, d, d, d, d, D_0047D6B4);
        }
        UiFadeWidgetAlpha_290690(D_00482360, 0x184, 0.0f, D_0047D6BC, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x14B, 0.0f, D_0047D6BC, -1.0f);
        obj = UiFindWidget_290460(D_00482360, 0xD7);
        if (obj != 0) {
            ch = GetMenuResGroup_206a40();
            *(s32 *)(obj + 0x20) = ResGroupListFindValueById_42c3a0(ch, 0x3A2);
            MenuPartyPanelIconSizesResetMaybe_29ddf0(D_00482370, 0xD7);
            *(s32 *)(obj + 0x20) = ResGroupListFindValueById_42c3a0(ch, wrap + 0x3A2);
        }
        MenuSetCursorPos_29faf0(D_00482370, cur, wrap);
        MenuLayoutPartyPanelMaybe_29cfb0(D_00482370, 0xD7, cur, wrap, 0);
        MenuLayoutPartyFramesMaybe_29cb70(D_00482370, 0xB8, cur, wrap);
        MenuSetPartyEquipIcon_29ec60(D_00482370, p[0], 0x113, 0);
        MenuSetPartyEquipIcon_29ec60(D_00482370, p[0], 0x114, 1);
        MenuSetPartyEquipIcon_29ec60(D_00482370, p[0], 0x115, 2);
        MenuSetPartyEquipIcon_29ec60(D_00482370, p[0], 0x116, 3);
        i = 0;
        do {
            v = *(s32 *)((u32)&p[i]);
            if (v < 3) {
                t = (u16)(v + 0xF5);
            } else {
                t = (u16)(v + 0xF8);
            }
            {
                s32 one = 1;
                UiSetWidgetsVisibleById_291110(D_00482360, t, one, one);
            }
            i++;
        } while (i < 2);
    } else {
        ta = (u16)(x + 0xDF);
        tb = (u16)(y + 0xDF);
        gm = GetGameData_1fede0();
        f = UiGetWidgetAlpha_290770(D_00482360, ta = (u16)ta);
        if (f >= D_0047D35C) {
            {
                f32 o = 1.0f;
                UiFadeWidgetColor_2904e0(D_00482360, ta, o, o, o, o, D_0047D6C0);
            }
            {
                f32 d = D_0047D288;
                UiFadeWidgetColor_2904e0(D_00482360, tb, d, d, d, 1.0f, D_0047D6C0);
            }
            cur = MenuGetCharaSel_29fa30(D_00482370);
            {
                s32 a0 = p[0];
                s32 b1;
                if ((a0 < n && p[1] >= n) || (a0 >= n && p[1] < n)) {
                    if (CharaCanBeLeader_3ae200(PartyGetMemberChara_3c2420(*(s32 *)(gm + 0x18), cur), 0) != 0) {
                        PartySetLeaderId_3c27c0(*(s32 *)(gm + 0x18), PartyGetSlotId_3c3120(*(s32 *)(gm + 0x18), cur));
                    } else {
                        PartySetLeaderId_3c27c0(*(s32 *)(gm + 0x18), 0);
                    }
                } else if (a0 < 3 && (b1 = p[1]) < n) {
                    if (a0 == cur) {
                        cur = b1;
                    } else if (b1 == cur) {
                        cur = a0;
                    }
                    MenuSetCharaSel_29fa20(D_00482370, cur);
                    UiSetWidgetPos_290f60(D_00482360, 0x132, D_0047ECF0[cur], -n);
                }
            }
        } else if (f <= 1.0f) {
            MenuSetCursorPos_29faf0(D_00482370, cur, wrap);
            StateMachineSetState_28ede0(D_0048235C, 0x4B, 0);
        }
    }
    UiSetWidgetsVisibleById_291110(D_00482360, 0x11F, 0, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x120, 0, 1);
    UiSetWidgetPos_290f60(D_00482360, 0x11F, 0, 0);
    UiSetWidgetPos_290f60(D_00482360, 0x120, 0, 0);
    return 1;
}
