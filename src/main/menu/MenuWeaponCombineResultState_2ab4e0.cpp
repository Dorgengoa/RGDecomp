#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s32 w[4];
} Tmp;

typedef void (*VFn)(s32, void *);

extern "C" {
extern void Sprintf_1343b8(void *, s32, void *);
extern void SoundPlayDefault_1b9ae0(s32, s32, s32);
extern void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void StreamPlayMwv_207340(s32, s32, f32);
extern void ReturnZero_207fe0(void);
extern void UiSetItemIconUv_288e50(s32, s32, s32, s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSelFrameAnimStep_28d820(void *, s32);
extern s32 UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void GetGridCellPosOffset_28ecd0(s32, s32 *, s32 *, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetTextStringPos_290b20(s32, s32, void *, s32, s32, s32);
extern s32 UiWidgetIsMoving_290d30(s32, s32);
extern void UiMoveWidget_290e00(s32, s32, s32, s32, s32, f32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern s32 MenuGetSelItem_2a02d0(s32);
extern void MenuItemPageRefresh_2a03d0(s32, s32, s32, s32, s32, s32, s32);
extern s32 MenuItemInfoPopupShow_2a33e0(s32, s32, s32, s32, void *, s32, s32, s32, f32);
extern void MenuItemInfoWidgetsCache_2a65f0(void *);
extern s32 MenuWeaponCombineResultModelMotionIsFinished_2a8650(void);
extern void MenuWeaponCombineResultModelPlaceAtCell_2a8690(s32, s32);
extern void MenuGridGetCursor_2abb30(s32, s32 *, s32 *);
extern void MenuItemSelectTab_2b3550(s32, s32, s32);
extern void MenuWeaponCombineAnimTickMaybe_361cd0(s32);
extern void MenuWeaponCombineAutoHideTick_362700(s32);
extern s32 D_004659F0[];
extern f32 D_0047D5D0;
extern f32 D_0047D734;
extern f32 D_0047D738;
extern f32 D_0047D73C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482374;
extern s32 D_00482384;
extern s32 D_004823D8;
extern s32 D_004823E4;
extern s8 D_004824F8;
extern u8 D_00483070;
extern u8 D_004DB430[];
extern u8 D_004DB5B0[];
extern u8 D_004DB5F0[];
s32 MenuWeaponCombineResultState_2ab4e0(s32 arg0, s32 arg1);
}

class VObj {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void f17(void *);
};



s32 MenuWeaponCombineResultState_2ab4e0(s32 arg0, s32 arg1)
{
    s32 ax;
    s32 ay;
    s32 bx;
    s32 by;
    s32 cx;
    s32 cy;
    Tmp t0;
    Tmp t1;
    Tmp t2;
    s32 o;
    s32 m;
    s32 v;
    s32 n;
    s32 e;

    if (arg1 != 0) {
        ReturnZero_207fe0();
        if (*(s32 *)(D_00482384 + 0x78) == 0) {
            UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D734, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x78, 0.0f, D_0047D734, -1.0f);
            MenuItemInfoWidgetsCache_2a65f0(&t0);
            MenuItemInfoPopupShow_2a33e0(D_00482374, 0, 0x1AA, 0x1A9, &t0, 0x68, 0x15E, -1, 2.0f);
            SoundPlayDefault_1b9ae0(D_004823E4, 8, 0);
        }
        *(s8 *)(D_00482384 + 0x61) = 2;
        UiSetWidgetsVisibleById_291110(D_00482360, 0x148, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x148, 0.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x27, 0);
        D_004824F8 = 0;
    }
    o = D_00482384;
    MenuWeaponCombineAutoHideTick_362700(o);
    MenuWeaponCombineAnimTickMaybe_361cd0(o);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    m = UiEntryListFindByTag_28ea40(D_00482364, 3);
    if (*(u8 *)(D_00482384 + 0x80) != 0 && D_004824F8 == 0) {
        v = *(s32 *)(D_00482384 + 0x7C);
        if (v == 0) {
            v = MenuGetSelItem_2a02d0(D_00482374);
        }
        e = UiGetWidgetSprite_28fe10(D_00482360, 0x147, 0);
        if (e == 0) {
            return 0;
        }
        UiSetItemIconUv_288e50(e, *(s16 *)(*(s32 *)(v + 0x10) + 0x2C), 0x28, 0x2D);
        e = UiGetWidgetSprite_28fe10(D_00482360, 0x14A, 0);
        if (e == 0) {
            return 0;
        }
        UiSetItemIconUv_288e50(e, *(s16 *)(*(s32 *)(v + 0x10) + 0x2C), 0x28, 0x2D);
        ((VObj *)v)->f17(D_004DB5B0);
        if (D_00483070 != 0) {
            Sprintf_1343b8(D_004DB5F0, MsgTableLookup_28aa30(D_004823D8, 0x420), D_004DB5B0);
        } else {
            Sprintf_1343b8(D_004DB5F0, MsgTableLookup_28aa30(D_004823D8, 0x464), D_004DB5B0);
        }
        UiSetTextStringPos_290b20(D_00482360, 0x149, D_004DB5F0, -1, -1, 0);
        MenuGridGetCursor_2abb30(*(u8 *)(D_00482384 + 0x82), &ax, &ay);
        UiSetWidgetPos_290f60(D_00482360, 0x147, 0x2D, 0x12C);
        UiFadeWidgetAlpha_290690(D_00482360, 0x147, 1.0f, D_0047D738, 0.5f);
        UiMoveWidget_290e00(D_00482360, 0x147, (s32)(2.0f + (98.0f + (f32)(ax * *(s16 *)(m + 8)))), (s32)((73.0f + (f32)(ay * *(s16 *)(m + 0xA))) - 1.0f), 3, D_0047D73C, 0.0f);
        if (*(u8 *)(D_00482384 + 0x82) != 0) {
            MenuItemSelectTab_2b3550(*(s32 *)(D_00482374 + 0x2C), 0, 1);
            n = *(s32 *)(D_00482374 + 0x30);
            UiSetSpriteSizeUvSize_28f670(D_00482360, 0x76, 0, 0, 0, 0, n);
            m = UiEntryListFindByTag_28ea40(D_00482364, 3);
            *(s16 *)(m + 0x14) = n % D_004659F0[0];
            *(s16 *)(m + 0x16) = n / D_004659F0[0];
        }
        MenuItemInfoWidgetsCache_2a65f0(&t1);
        MenuItemInfoPopupShow_2a33e0(D_00482374, 0, 0x1AA, 0x1A9, &t1, 0x68, 0x15E, -1, 1.0f);
        D_004824F8 = 1;
    }
    if (D_004824F8 == 0x14) {
        if (MenuWeaponCombineResultModelMotionIsFinished_2a8650() != 0) {
            UiFadeWidgetAlpha_290690(D_00482360, 0x148, 1.0f, D_0047D73C, -1.0f);
            v = *(s32 *)(D_00482384 + 0x7C);
            if (v != 0) {
                MenuItemInfoWidgetsCache_2a65f0(&t2);
                MenuItemInfoPopupShow_2a33e0(D_00482374, v, 0x1AA, 0x1A9, &t2, 0x68, 0x15E, -1, 2.0f);
            }
            D_004824F8 = 2;
        }
    } else if (D_004824F8 == 1) {
        if (UiWidgetIsMoving_290d30(D_00482360, 0x147) == 0) {
            MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0x31, 0x30);
            UiSetWidgetPos_290f60(D_00482360, 0x148, 0xA5, 0xAF);
            MenuGridGetCursor_2abb30(*(u8 *)(D_00482384 + 0x82), &bx, &by);
            MenuWeaponCombineResultModelPlaceAtCell_2a8690(bx, by);
            v = *(s32 *)(D_00482384 + 0x7C);
            if (v == 0) {
                v = MenuGetSelItem_2a02d0(D_00482374);
            }
            if (**(s16 **)(v + 0x10) == 0x3EC3) {
                StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0xF, D_0047D5D0);
                StreamPlayMwv_207340(0x321, 0, 1.0f);
                *(s32 *)(D_00482384 + 0x78) = -1;
            } else {
                SoundPlayDefault_1b9ae0(D_004823E4, 6, 0);
            }
            if (*(u8 *)(D_00482384 + 0x82) != 0) {
                n = *(s32 *)(D_00482374 + 0x30);
                m = UiEntryListFindByTag_28ea40(D_00482364, 3);
                *(s16 *)(m + 0x14) = n % D_004659F0[0];
                *(s16 *)(m + 0x16) = n / D_004659F0[0];
                GetGridCellPosOffset_28ecd0(m + 4, &cx, &cy, -0xE, 0x1C);
                UiSetWidgetPos_290f60(D_00482360, 0x227, cx, cy);
            }
            D_004824F8 = 0x14;
        }
    } else if (D_004824F8 == 2) {
        if (!(UiGetWidgetAlpha_290770(D_00482360, 0x148) < 1.0f)) {
            StateMachineSetState_28ede0(D_0048235C, 0x24, 0);
        }
    }
    ReturnZero_207fe0();
    return 1;
}
