#include "types.h"

class P39CA50 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual s32 f21();
    virtual s32 f22();
};

extern "C" {
extern void *memset(void *, s32, u32);
extern s32 CharaIsNearLeaderMaybe_1fb230(s32, s32);
extern u8 *GetGameData_1fede0(void);
extern s32 GetMenuResGroup_206a40(void);
extern void UiLayoutWindowFrame_28b8e0(s32, s32, s32, s32);
extern void UiLayoutFrameRectsMaybe_28bbb0(s32, s32, s32);
extern void UiWindowFitToText_28d0c0(void *, s32, s32, s32);
extern u8 *UiEntryListFindByTag_28ea40(void *, s32);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void UiSetTextString_28f510(void *, s32, s32, s32);
extern s32 UiGetWidgetText_28f620(void *, s32, s32);
extern void UiSetSpriteUvW_28f850(void *, s32, s32, s32);
extern void UiSetSpriteW_28fbf0(void *, s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(void *, s32, s32);
extern u8 *UiFindWidget_290460(void *, s32);
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(void *, s32);
extern void UiSetWidgetAlpha_2907a0(void *, s32, f32);
extern void UiSetTextColor_290a40(void *, s32, s32, s32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern s32 CharaCanBeLeader_3ae200(P39CA50 *, s32);
extern s32 PartyCountMembers_3c2010(u8 *, s32, s32);
extern P39CA50 *PartyGetMemberChara_3c2420(u8 *, s32);
extern P39CA50 *PartyGetLeaderChara_3c2820(u8 *);
extern s32 ResGroupListFindValueById_42c3a0(s32, s32);
extern f32 D_0047D7C4;
extern u8 D_00483600;
extern u8 D_004E9610[];
extern u8 D_004E9630[];
}

extern "C" s32 LeaderSwitchOpenState_39ca50(s32 pad0, s32 arg1) {
    s32 b[0xD];
    s16 cnt;
    u8 *d;
    s32 m;
    u8 *w;
    u8 *s1;
    s32 e;
    P39CA50 *lst;
    s32 j;
    s32 i;
    P39CA50 *it;
    s32 col;

    if (arg1 != 0) {
        cnt = 0;
        d = GetGameData_1fede0();
        if (d == 0) {
            return 0;
        }
        m = GetMenuResGroup_206a40();
        if (m == 0) {
            return 0;
        }
        w = UiFindWidget_290460(D_004E9610, 2);
        if (w == 0) {
            return 0;
        }
        s1 = UiEntryListFindByTag_28ea40(D_004E9630, 0x7149);
        if (PartyCountMembers_3c2010(*(u8 **)(d + 0x18), 1, 1) >= 3) {
            e = ResGroupListFindValueById_42c3a0(m, 0x715D);
            *(s32 *)(w + 0x20) = e;
            if (e == 0) {
                return 0;
            }
            UiLayoutWindowFrame_28b8e0(e, 0x60, 0x3E, 2);
            *(s16 *)(s1 + 0xE) = 1;
        lst = PartyGetLeaderChara_3c2820(*(u8 **)(d + 0x18));
        j = 0;
        for (i = 0; i < PartyCountMembers_3c2010(*(u8 **)(d + 0x18), 1, 1); i++) {
            it = PartyGetMemberChara_3c2420(*(u8 **)(d + 0x18), i);
            if (lst->f21() == it->f21()) {
                continue;
            }
            UiSetTextString_28f510(D_004E9610, 2, it->f22(), j);
            col = 0xFF202020;
            if (CharaIsNearLeaderMaybe_1fb230(*(s32 *)((u8 *)it + 0xC), -1) != 0 && CharaCanBeLeader_3ae200(it, 0) != 0 && !(*(u8 *)((u8 *)it + 0x4B4) & 1) && !(*(u8 *)(*(u8 **)(d + 0x18) + 0x42D0) & 1)) {
                col = 0xFF303030;
                cnt++;
            }
            UiSetTextColor_290a40(D_004E9610, 2, col, j);
            j++;
        }
        UiSetWidgetsVisibleById_291110(D_004E9610, 3, 1, 1);
        UiSetWidgetAlpha_2907a0(D_004E9610, 3, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 3, 1.0f, D_0047D7C4, -1.0f);
        UiSetWidgetAlpha_2907a0(D_004E9610, 2, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 2, 1.0f, D_0047D7C4, -1.0f);
        UiSetWidgetAlpha_2907a0(D_004E9610, 1, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 1, 1.0f, D_0047D7C4, -1.0f);
        UiSetWidgetPos_290f60(D_004E9610, 4, -0x14, 5);
        } else {
            e = ResGroupListFindValueById_42c3a0(m, 0x715E);
            *(s32 *)(w + 0x20) = e;
            if (e == 0) {
                return 0;
            }
            UiLayoutFrameRectsMaybe_28bbb0(e, 0x60, 0x24);
            *(s16 *)(s1 + 0xE) = 0;
        lst = PartyGetLeaderChara_3c2820(*(u8 **)(d + 0x18));
        j = 0;
        for (i = 0; i < PartyCountMembers_3c2010(*(u8 **)(d + 0x18), 1, 1); i++) {
            it = PartyGetMemberChara_3c2420(*(u8 **)(d + 0x18), i);
            if (lst->f21() == it->f21()) {
                continue;
            }
            UiSetTextString_28f510(D_004E9610, 2, it->f22(), j);
            col = 0xFF202020;
            if (CharaIsNearLeaderMaybe_1fb230(*(s32 *)((u8 *)it + 0xC), -1) != 0 && CharaCanBeLeader_3ae200(it, 0) != 0 && !(*(u8 *)((u8 *)it + 0x4B4) & 1) && !(*(u8 *)(*(u8 **)(d + 0x18) + 0x42D0) & 1)) {
                col = 0xFF303030;
                cnt++;
            }
            UiSetTextColor_290a40(D_004E9610, 2, col, j);
            j++;
        }
            UiSetTextString_28f510(D_004E9610, 2, 0, 1);
        }
        UiSetSpriteW_28fbf0(D_004E9610, 2, 0, 4);
        UiSetSpriteUvW_28f850(D_004E9610, 2, 0, 4);
        UiSetWidgetsVisibleById_291110(D_004E9610, 1, 1, 1);
        UiSetWidgetPos_290f60(D_004E9610, 1, 0xD2, 0xC4);
        UiSetWidgetsVisibleById_291110(D_004E9610, 2, 1, 1);
        UiSetWidgetPos_290f60(D_004E9610, 2, 0xD2, 0xC4);
        memset(b, 0, 0x34);
        b[0] = UiGetWidgetSprite_28fe10(D_004E9610, 3, 0);
        b[1] = UiGetWidgetText_28f620(D_004E9610, 3, 0);
        b[4] = 0x3C;
        b[5] = 0xC;
        b[6] = 0x1C;
        b[7] = 8;
        b[8] = 0;
        b[9] = 0;
        b[10] = 0x200;
        b[11] = 0x148;
        *(s16 *)&b[12] = 4;
        UiWindowFitToText_28d0c0(b, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_004E9610, 3, 1, 1);
        UiSetWidgetAlpha_2907a0(D_004E9610, 3, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 3, 1.0f, D_0047D7C4, -1.0f);
        UiSetWidgetAlpha_2907a0(D_004E9610, 2, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 2, 1.0f, D_0047D7C4, -1.0f);
        UiSetWidgetAlpha_2907a0(D_004E9610, 1, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 1, 1.0f, D_0047D7C4, -1.0f);
        UiSetWidgetPos_290f60(D_004E9610, 4, -0x14, 5);
        if (cnt == 0) {
            UiSetWidgetsVisibleById_291110(D_004E9610, 1, 0, 1);
            UiSetWidgetsVisibleById_291110(D_004E9610, 2, 0, 1);
            UiSetWidgetsVisibleById_291110(D_004E9610, 3, 0, 1);
            StateMachineSetState_28ede0(&D_00483600, 0x714B, 1);
        }
    }
    if (!(UiGetWidgetAlpha_290770(D_004E9610, 3) < 1.0f)) {
        StateMachineSetState_28ede0(&D_00483600, 0x714A, 1);
    }
    return 1;
}
