/* rgp:protos */
#line 1
#include "types.h"

class VObj {
public:
    VC_VPTR_MEMBER;   
       
       
       
    s32 v48() { return VCM0(s32, 0x48); }
    void v4C(bool a0) { VCM(void, (void *, bool), 0x4C, a0); }
};

struct Ent {
    s8 _0[4];
    s16 x4;
    s16 x6;
    s8 _8[0xE];
    s16 x16;
};

struct Info {
    s8 _0[0x12];
    s16 x12;
    s8 _14[2];
    s16 x16;
};

struct Rec32 {
    s8 _0[8];
    s16 x8;
    s8 _a[0x12];
    u16 x1C;
    s8 _1e[2];
};

struct Col {
    s8 _0[0xC];
    u32 xC;
};

struct Obj {
    s8 _0[0x20];
    Rec32 *x20;
    s8 _24[4];
    Col *x28;
};

extern "C" {
s32 PadIsTriggered_1839f0(void *, s32);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
u8 *GetGameData_1fede0(void);
s32 MenuGridCursorInput_28e170(void *, void *, s32, s32);
void MenuGridCursorRequestSe_28e9e0(void *, s32);
Ent *UiEntryListFindByTag_28ea40(void *, s32);
void UiEntryListSelectByTag_28ea90(void *, s32, s32);
Info *UiEntryListGetCurrentData_28ec60(void *);
void StateMachineSetState_28ede0(s32, s32, s32);
Obj *UiFindWidget_290460(s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, f32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void MenuCycleCharaSel_3537c0(Info *, s32);
void MenuTacticsAbilityListSetRowRange_3542e0(void);
void MenuInfoPopupShowTextMaybe_355b60(s32, s16 *, s32, s32, s32, s32, f32);
s16 * IterSeek_36fff0(void *, s32, int, int);
void IterInit_370170(void *, void *, int, int);
void CharaAbilityViewCtor_3a8180(void *, s32, s32, s32);
VObj *CharaFindSlotByRecId_3ad390(s32, s32);
s32 PartyGetSlotChara_3c2fb0(s32, s32);
extern f32 D_0047D288 __attribute__((section(".sdata")));
extern f32 D_0047D5D0;
extern f32 D_0047D5F8;
extern f32 D_0047D5FC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern u8 *D_00482364;
extern s32 D_0048237C;
extern s16 D_00482F14;
extern s32 D_00482F18;
extern u8 D_004B2570[];
s32 MenuTacticsAbilityToggleState_353e30(s32 arg0, s32 arg1);
}

s32 MenuTacticsAbilityToggleState_353e30(s32 arg0, s32 arg1) {
    u8 sp98[8];
    u8 sp90[8];
    u8 sp80[16] __attribute__((aligned(16)));
    u8 sp70[16] __attribute__((aligned(16)));
    s32 r;
    Info *info;
    s32 obj;
    s16 *q;
    VObj *vo;
    s8 flag;
    Rec32 *recs;
    s32 id;
    Col *col;
    Rec32 *recs2;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x23, 0);
        MenuTacticsAbilityListSetRowRange_3542e0();
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
    info = UiEntryListGetCurrentData_28ec60(D_00482364);
    if (r == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0xA1, 0);
    } else if (r == 1) {
        obj = PartyGetSlotChara_3c2fb0(*(s32 *)(GetGameData_1fede0() + 0x18), D_00482F14);
        if (obj == 0) {
            return 0;
        }
        CharaAbilityViewCtor_3a8180(sp80, obj, 3, -1);
        IterInit_370170(sp98, sp80, 0, 0);
        q = IterSeek_36fff0(sp98, info->x12 + info->x16, 0, 0);
        if (q == 0) {
            return 0;
        }
        vo = CharaFindSlotByRecId_3ad390(obj, *q);
        if (vo == 0) {
            return 0;
        }
        flag = (vo->v48() != 0) ^ 1;
        vo->v4C(flag);
        {
            Obj *e = UiFindWidget_290460(D_00482360, 0xD3);
            if (e == 0) {
                return 0;
            }
            recs = e->x20;
        }
        if (recs == 0) {
            return 0;
        }
        id = (u16)(info->x12 + 0xCA);
        {
            Obj *e = UiFindWidget_290460(D_00482360, id);
            if (e == 0) {
                return 0;
            }
            col = e->x28;
        }
        if (col == 0) {
            return 0;
        }
        UiSetWidgetColor_2905b0(D_00482360, 0xD5, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        {
            Obj *e = UiFindWidget_290460(D_00482360, 0xD5);
            if (e == 0) {
                return 0;
            }
            recs2 = e->x20;
        }
        if (recs2 == 0) {
            return 0;
        }
        if (flag) {
            recs[info->x12].x8 = 0x60;
            col->xC = 0xFF303030;
            UiSetWidgetColor_2905b0(D_00482360, id, 1.0f, 1.0f, 1.0f, 1.0f);
            recs2[info->x12].x1C |= 8;
        } else {
            recs[info->x12].x8 = 0x70;
            col->xC = 0xFF202020;
            UiSetWidgetColor_2905b0(D_00482360, id, D_0047D288, D_0047D288, D_0047D288, 1.0f);
            if (recs2[info->x12].x1C & 8) {
                recs2[info->x12].x1C ^= 8;
            }
        }
    } else if (*(s32 *)(D_00482364 + 0x14) == 1) {
        Ent *ent;
        MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        ent = UiEntryListFindByTag_28ea40(D_00482364, 0x21);
        ent->x16 = 0;
        UiSetWidgetPos_290f60(D_00482360, 0x1A6, ent->x4, ent->x6 + ent->x16 * 21);
        UiMoveWidgetUniform_290f50(D_00482360, 0x38, 0x11A, -0x28, D_0047D5F8, 0);
        UiMoveWidgetUniform_290f50(D_00482360, 0x37, 0x11D, -0x25, D_0047D5F8, 0);
        StateMachineSetState_28ede0(D_0048235C, 0x9A, 0);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0xC) != 0) {
        MenuCycleCharaSel_3537c0(info, 0);
        UiSetWidgetPos_290f60(D_00482360, 0xC6, 0x18, 0x39);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
        SoundPlayScaledVolume_1b9520(D_00482F18, 5, 0, 1.0f);
        obj = PartyGetSlotChara_3c2fb0(*(s32 *)(GetGameData_1fede0() + 0x18), D_00482F14);
        if (obj == 0) {
            return 0;
        }
        CharaAbilityViewCtor_3a8180(sp70, obj, 3, -1);
        IterInit_370170(sp90, sp70, 0, 0);
        MenuInfoPopupShowTextMaybe_355b60(D_0048237C, IterSeek_36fff0(sp90, info->x12 + info->x16, 0, 0), 0x1AA, 0x1A9, 0x5D, 0x146, D_0047D5D0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x1A6, 0.0f, D_0047D5FC, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0xA2, 0);
    }
    return 1;
}
