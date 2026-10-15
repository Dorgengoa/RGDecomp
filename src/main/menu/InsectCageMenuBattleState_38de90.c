#include "types.h"

extern void ModelSetPos_151110(u8 *, s32 *);
extern s32 MotionListIsFinished_171d90(u8 *, s32);
extern void MotionListResetAll_171e00(u8 *);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern void ModelObjPlayMotionByName_1867a0(u8 *, void *, s32);
extern void PlayMenuSe_289ef0(s32);
extern void MsgFormat_28a9a0(void *, s32, void *, s32);
extern void MsgFormatParamsClear_28a9f0(void *);
extern void MsgFormatParamsCtor_28aa00(void *);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void InsectCageSePlay_3844b0(void *, s32);
extern void InsectCageSeStopLoops_384540(void *);
extern void MenuObjSlotClear_384990(u8 *);
extern void MenuObjSlotsReleaseByKey_3857b0(u8 *, s32);
extern void MenuObjBattlePairAssign_385c70(u8 *, s32, s32);
extern s32 MenuObjInsectIsMaxLevel_386b60(s32);
extern s32 MenuObjInsectGetLevel_386b90(s32);
extern s32 MenuObjInsectIsFullyGrown_386c40(s32);
extern s32 MenuObjInsectIsAdult_386c90(s32);
extern s32 MenuObjInsectGetName_386d40(s32);
extern void MenuObjSetBattlePartner_387ca0(s32, s32);
extern void UiFitCenterWindow_388270(s32, s32);
extern s32 InsectCageMenuMsgLookup_389d30(s32);
extern void InsectCageMenuApplyItemToPair_38e470(void);
extern s32 InsectCageMenuPairSelectInputMaybe_38e540(s32, s32, s32);
extern void InsectCageMenuSetStateFlagMaybe_390aa0(s32, s32);
extern void InsectCageMenuSelectEntry_390d40(s32, s32);
extern s32 InsectCageMenuGetCurCageItem_391030(void);
extern void InsectRecClearPairEntries_3cf2f0(s32);
extern char *strcat(char *, const char *);
extern char D_00463EB8[];
extern u8 D_004640F8[];
typedef struct { f32 x, y, z, w; } V4;
extern f32 D_0047FBC0;
extern f32 D_0047FBC4;
extern f32 D_0047FBC8;
extern f32 D_0047FBCC;
extern s16 D_0047FBD4;
extern s32 D_004832A0;
extern u8 *D_004832D8;
extern char *D_00483304;
extern s32 D_00483380[1];
extern s32 D_00483384;
extern s8 D_00483388[2];
extern u8 D_0048338C[2];
extern u8 D_00483390[2];
extern u8 D_00483394[2];
extern s16 D_00483398;
extern u8 D_004B2570[];
extern s32 D_004E9528[];
extern s32 D_004E9548[];

typedef struct {
    s32 x0;
    u8 pad4[0x1C - 4];
    s32 x1C;
    s32 x20;
    u8 pad24[0xB0 - 0x24];
} Info;

s32 InsectCageMenuBattleState_38de90(s32 arg0, s32 arg1) {
    Info info;
    char buf[0x200];
    V4 v;
    s32 t;
    u8 *o;
    s32 i;
    s32 *pv;
    u8 *pf;
    s32 k;

    t = InsectCageMenuGetCurCageItem_391030();
    switch (D_0047FBD4) {
    case 0:
        if (InsectCageMenuPairSelectInputMaybe_38e540(arg0, arg1, 0) != 0) {
            D_0047FBD4++;
        }
        break;
    case 1:
        if ((u8)(D_004E9528[0] < 1) && (u8)(D_004E9548[0] < 1)) {
            InsectCageMenuApplyItemToPair_38e470();
            MenuObjSetBattlePartner_387ca0(D_00483380[0], D_00483384);
            MenuObjSetBattlePartner_387ca0(D_00483384, D_00483380[0]);
            MenuObjBattlePairAssign_385c70(D_004832D8, D_00483380[0], D_00483384);
            D_0047FBD4++;
        }
        break;
    case 2:
        InsectCageSePlay_3844b0(&D_004832A0, 0);
        InsectCageMenuSetStateFlagMaybe_390aa0(1, 0);
        InsectCageMenuSetStateFlagMaybe_390aa0(2, 0);
        D_00483398 = 0x168;
        D_0047FBD4++;
        break;
    case 3:
        if (--D_00483398 > 0) {
            break;
        }
        InsectCageMenuSetStateFlagMaybe_390aa0(1, 1);
        InsectCageMenuSetStateFlagMaybe_390aa0(2, 1);
        MenuObjSetBattlePartner_387ca0(D_00483380[0], 0);
        MenuObjSetBattlePartner_387ca0(D_00483384, 0);
        InsectCageSeStopLoops_384540(&D_004832A0);
        InsectCageSePlay_3844b0(&D_004832A0, 7);
        MenuObjSlotsReleaseByKey_3857b0(D_004832D8, D_00483380[0]);
        {
            s32 b_ = D_00483384;
            o = D_004832D8;
            *(s32 *)(o + 0x3210) = D_00483380[0];
            *(s32 *)(o + 0x3214) = b_;
        }
        ModelObjPlayMotionByName_1867a0(o + 0x3220, D_004640F8, 6);
        D_0047FBD4++;
        break;
    case 4:
        if (MotionListIsFinished_171d90(D_004832D8 + 0x3410, -1) != 0) {
            o = D_004832D8;
            MenuObjSlotClear_384990(o + 0x3210);
            MotionListResetAll_171e00(o + 0x3410);
            { f32 *pf_ = (f32 *)&v; pf_[0] = D_0047FBC0; pf_[1] = D_0047FBC4; pf_[2] = D_0047FBC8; pf_[3] = D_0047FBCC; }
            v.y = -50.0f;
            v.x = 0.0f;
            v.z = 0.0f;
            ModelSetPos_151110(o + 0x3220, (s32 *)&v);
            InsectRecClearPairEntries_3cf2f0(t);
            MsgFormatParamsCtor_28aa00(&info);
            info.x1C = MenuObjInsectGetName_386d40(D_00483380[0]);
            info.x20 = MenuObjInsectGetName_386d40(D_00483384);
            MsgFormat_28a9a0(D_00483304 + 0x800, InsectCageMenuMsgLookup_389d30(0x4D8), &info, 1);
            for (i = 0; i < 2; i++) {
                buf[0] = 0;
                MsgFormatParamsClear_28a9f0(&info);
                pv = &D_00483380[i];
                info.x1C = MenuObjInsectGetName_386d40(*pv);
                info.x0 = MenuObjInsectGetLevel_386b90(*pv);
                pf = &D_00483390[i];
                if (*pf != 0) {
                    k = 0x4DB;
                } else {
                    k = 0x4D9;
                }
                if (k > 0) {
                    strcat(D_00483304 + 0x800, D_00463EB8);
                    MsgFormat_28a9a0(buf, InsectCageMenuMsgLookup_389d30(k), &info, 1);
                    strcat(D_00483304 + 0x800, buf);
                }
                k = -1;
                if (D_00483394[i] == 0 && MenuObjInsectIsMaxLevel_386b60(*pv) != 0) {
                    k = 0x4DD;
                } else if (D_00483388[i] != info.x0) {
                    k = 0x4DA;
                }
                if (k > 0) {
                    strcat(D_00483304 + 0x800, D_00463EB8);
                    MsgFormat_28a9a0(buf, InsectCageMenuMsgLookup_389d30(k), &info, 1);
                    strcat(D_00483304 + 0x800, buf);
                }
                k = -1;
                if (*pf == 0 && MenuObjInsectIsFullyGrown_386c40(*pv) != 0) {
                    k = 0x4DC;
                } else if (D_0048338C[i] == 0 && MenuObjInsectIsAdult_386c90(*pv) != 0) {
                    k = 0x4C4;
                }
                if (k > 0) {
                    strcat(D_00483304 + 0x800, D_00463EB8);
                    MsgFormat_28a9a0(buf, InsectCageMenuMsgLookup_389d30(k), &info, 1);
                    strcat(D_00483304 + 0x800, buf);
                }
            }
            UiFitCenterWindow_388270(0x75DA, 1);
            UiSetWidgetsVisibleById_291110(arg1, 0x75DA, 1, 1);
            InsectCageSePlay_3844b0(&D_004832A0, 4);
            D_0047FBD4++;
        }
        break;
    case 5:
        if (PadIsTriggered_1839f0(D_004B2570, 0x60) != 0) {
            D_0047FBD4 = -1;
            InsectCageMenuSetStateFlagMaybe_390aa0(1, 0);
            InsectCageMenuSetStateFlagMaybe_390aa0(2, 0);
            PlayMenuSe_289ef0(5);
            UiSetWidgetsVisibleById_291110(arg1, 0x75DA, 0, 1);
            InsectCageMenuSelectEntry_390d40(0x7531, 0);
        }
        break;
    }
    return 1;
}
