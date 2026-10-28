/* PARK: m2c cannot decompile -- "Unable to determine jump table for jr
   instruction." Needs a jump-table reconstruction pass this lane's budget
   does not cover. Not attempted. */
/* s49m: MATCH multi-text 3 functions mscore model */
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v394(s32 a, s32 b) { VCM(void, (void *, s32, s32), 0x394, a, b); }
};

extern "C" void CharaEquipWeaponSlot1_2a9a30(Obj *obj, s32 arg1)
{
    obj->v394(1, arg1);
}

extern "C" void func_002A9A50(Obj *obj, s32 arg1)
{
    obj->v394(0, arg1);
}

extern "C" {
extern s32 D_00482360;
extern s32 D_00482364;
extern u8 *D_00482374;
extern s32 D_00481BBC;
extern s32 D_0048235C;
extern u8 D_004824CC;
extern f32 D_0047D6F8;
extern f32 D_0047D6D0;
extern f32 D_0047D580;
extern u8 D_004DB430[];
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
s32 UiEntryListFindByTag_28ea40(s32, s32);
s32 MenuGetItemAtCell_2a7000(s32, s32);
void MenuItemEquipCompareShowMaybe_2a4310(u8 *, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
void UiSetSpriteU_28f930(s32, s32, s32, s32);
s32 MsgTableLookup_28aa30(s32, s32);
void UiSetTextString_28f510(s32, s32, s32, s32);
void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
void UiSelFrameAnimStep_28d820(u8 *, s32);
void MenuCursorBobUpdate_2a9c00(void);
void StateMachineSetState_28ede0(s32, s32, s32);
}

extern "C" s32 func_002A9A70(s32 arg0, s32 arg1)
{
    s32 v;

    if (arg1 != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D6F8, -1.0f);
        v = UiEntryListFindByTag_28ea40(D_00482364, 3);
        v = MenuGetItemAtCell_2a7000(*(s8 *)(D_00482374 + 0x11), v + 4);
        MenuItemEquipCompareShowMaybe_2a4310(D_00482374, v);
        UiSetWidgetsVisibleById_291110(D_00482360, 0xA4, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0xA4, 0x78, 0x7D);
        UiFadeWidgetAlpha_290690(D_00482360, 0xA4, 1.0f, D_0047D6D0, D_0047D580);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        UiSetWidgetPos_290f60(D_00482360, 0xAB, 0x52, 0x88);
        UiSetSpriteU_28f930(D_00482360, 0xA5, 0x4C, 0);
        UiSetSpriteU_28f930(D_00482360, 0xA5, 0x18, 1);
        D_004824CC = 0;
        UiSetTextString_28f510(D_00482360, 0xA6, MsgTableLookup_28aa30(D_00481BBC, 0x52), 3);
        UiSetTextString_28f510(D_00482360, 0xA6, MsgTableLookup_28aa30(D_00481BBC, 0x53), 4);
        UiSetTextCenteredX_28f300(D_00482360, 0xA6, 0x82, 3);
        UiSetTextCenteredX_28f300(D_00482360, 0xA6, 0xD2, 4);
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    MenuCursorBobUpdate_2a9c00();
    StateMachineSetState_28ede0(D_0048235C, 0x44, 0);
    return 1;
}
