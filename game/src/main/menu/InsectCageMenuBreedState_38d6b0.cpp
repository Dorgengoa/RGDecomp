/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct Chr38 {
    u8 pad0[0x180];
    u128 m180;
    u8 pad190[0x96C - 0x190];
    s32 m96C;
    u8 pad970[0x984 - 0x970];
    s8 m984;
} Chr38;

typedef struct Ent38 {
    u8 pad0[0x10];
    s16 m10;
} Ent38;

typedef struct Obj3B70 {
    u8 pad0[0x44];
    void (*f44)(void *, f32);
} Obj3B70;

class Obj39C0 {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v44(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
};

typedef struct Scn38 {
    u8 pad0[0x39B0];
    Chr38 *m39B0;
    u8 pad39B4[0x39C0 - 0x39B4];
    u8 m39C0[0x3B70 - 0x39C0];
    Obj3B70 *m3B70;
    u8 pad3B74[0x3BB0 - 0x3B74];
    u8 m3BB0[4];
} Scn38;

extern "C" {
extern void MemStackReset_14d830(void *);
extern void ModelSetPos_151110(void *, void *);
extern s32 MotionListIsFinished_171d90(void *, s32);
extern void MotionListResetAll_171e00(void *);
extern f32 ModelObjGetMotionPhase_1add70(void *);
extern void ObjGetAttachNodePos_1adec0(Chr38 *, s32, void *);
extern void ModelObjPlayMotionByName_1867a0(void *, void *, s32);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern void MsgFormat_28a9a0(s32, void *, void *, s32);
extern void MsgFormatParamsCtor_28aa00(void *);
extern void LoadHandleFree_28b230(s32);
extern s32 LoadHandleGetData_28b270(s32, void *);
extern s32 LoadHandleGetStatus_28b2e0(s32);
extern void LoadHandleRequestFile_28b550(s32, void *, s32, s32);
extern void LoadHandleInit_28b610(s32);
extern Ent38 *UiEntryListFindDataByTag_28ec30(void *, s32);
extern void PlayMenuSe_289ef0(s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuFadeSetColor_29ff90(s32, s32, s32, s32);
extern s32 MenuFadeIsIdle_29ffa0(s32);
extern void MenuFadeStep_29ffd0(s32, f32);
extern void MenuFadeStartFromColor_2a0020(s32);
extern void MenuFadeStartToColor_2a0040(s32);
extern void MenuObjLoopSoundUpdate_3843d0(void *);
extern void BitArraySetReturnOld_384360(void *, s32, s32);
extern void InsectCageSePlay_3844b0(void *, s32);
extern void MenuObjSlotClear_384990(void *);
extern void MenuObjBreedSlotAssign_385950(s32, Chr38 *, Chr38 *);
extern void MenuObjSlotsReleaseByKey_3857b0(s32, Chr38 *);
extern void MenuCursorObjSetVisible_386280(void *, s32);
extern void MenuObjBuildRandomRoute_3871a0(Chr38 *, void *, s32);
extern void MenuObjWalkUpdateMaybe_387390(Chr38 *, s32, s32);
extern void MenuObjLoadFromCfg_387930(Chr38 *, s32, s32, u8 *, s32);
extern void MenuObjSetBreedPartner_387c50(Chr38 *, Chr38 *);
extern void MenuObjTeardown_387d60(Chr38 *);
extern void MenuObjReset_387dc0(Chr38 *);
extern void UiFitCenterWindow_388270(s32, s32);
extern s32 InsectCageMenuMsgLookup_389d30(s32);
extern s32 InsectCageGetCollTris_389d70(s32 *);
extern void InsectCageMenuBuildObjList_3909a0(void);
extern void InsectCageMenuSetStateFlagMaybe_390aa0(s32, s32);
extern void InsectCageMenuSelectEntry_390d40(s32, s32);
extern Chr38 *MenuObjFindFree_390d80(s32 *);
extern void InsectCharaPathFormat_390de0(void *, s32, int, int);
extern s32 InsectCageMenuGetCurCageItem_391030(void);
extern s32 InsectCageMenuPairSelectInputMaybe_38e540(s32, s32, s32);
extern void InsectCageMenuApplyItemToPair_38e470(void);
extern s32 InsectBreedCreate_3cf0c0(s32);
extern void InsectRecClearPairEntries_3cf2f0(s32);
extern void InsectRecRemoveMsgsOfKind_3ceed0(s32, s32);

extern s16 D_0047FBD8;
extern f32 D_0047D2A8;
extern f32 D_0047D34C;
extern s32 D_00482374;
extern s32 D_004832A0;
extern u8 *D_004832A8;
extern s32 D_004832B8;
extern Scn38 *D_004832D8;
extern s32 D_004832E4;
extern s32 D_00483304;
extern Chr38 *D_00483380;
extern Chr38 *D_00483384;
extern s32 D_0048339C;
extern Chr38 *D_004833A0;
extern u128 D_004833B0 __attribute__((section(".sdata")));
extern s32 D_004833C0;
extern s16 D_004833C4;
extern s32 D_004E9528[];
extern s32 D_004E9548[];
extern Chr38 *D_004E94A0[];
extern u8 D_004E94C0[];
extern u8 D_004E94E0[];
extern u8 D_004B2570[];
extern u8 D_00464100[];

}
static inline s32 idle(s32 *p)
{
    return *p < 1;
}

extern "C" s32 InsectCageMenuBreedState_38d6b0(s32 arg0, s32 arg1)
{
    u8 buf110[0x44] __attribute__((aligned(16)));
    u8 buf60[0xB0] __attribute__((aligned(16)));
    u8 buf50[0x10] __attribute__((aligned(16)));
    s32 sp15C;
    s32 sp158;
    s32 sp154;
    s32 sys;
    f32 f;
    s32 i;
    s32 j;
    Chr38 *p;
    Chr38 **pp;
    Chr38 *c;
    s32 r;
    s32 h;
    Scn38 *scn;
    Chr38 *cur;

    sys = InsectCageMenuGetCurCageItem_391030();
    f = 0.25f;
    switch (D_0047FBD8) {
    case 0:
        if (InsectCageMenuPairSelectInputMaybe_38e540(arg0, arg1, 1) != 0) {
            D_0047FBD8++;
        }
        break;
    case 1:
        if (idle(D_004E9528) && idle(D_004E9548)) {
            InsectCageMenuApplyItemToPair_38e470();
            MenuObjSetBreedPartner_387c50(D_00483380, D_00483384);
            MenuObjSetBreedPartner_387c50(D_00483384, D_00483380);
            MenuObjBreedSlotAssign_385950((s32)D_004832D8, D_00483380, D_00483384);
            D_0047FBD8++;
        }
        break;
    case 2:
        D_004833C0 = 0xF0;
        D_0047FBD8++;
        InsectCageMenuSetStateFlagMaybe_390aa0(1, 0);
        InsectCageMenuSetStateFlagMaybe_390aa0(2, 0);
        MenuCursorObjSetVisible_386280(D_004E94C0, 0);
        break;
    case 3:
        if (--D_004833C0 <= 0) {
            InsectCageMenuSetStateFlagMaybe_390aa0(1, 1);
            InsectCageMenuSetStateFlagMaybe_390aa0(2, 1);
            for (i = 0; i < 5; i++) {
                p = D_004E94A0[i];
                if (p != 0) {
                    if (p != D_00483380 && p != D_00483384) {
                        BitArraySetReturnOld_384360((u8 *)p + 0x986, 8, 1);
                    } else {
                        BitArraySetReturnOld_384360((u8 *)p + 0x986, 8, 0);
                    }
                }
            }
            MenuFadeSetColor_29ff90(D_00482374, 0xFA, 0xFA, 0xFA);
            MenuFadeStartToColor_2a0040(D_00482374);
            D_0047FBD8++;
        }
        break;
    case 4:
        if (MenuFadeIsIdle_29ffa0(D_00482374) != 0) {
            for (j = 0; j < 5; j++) {
                p = D_004E94A0[j];
                if (p != 0 && (p == D_00483380 || p == D_00483384)) {
                    pp = &D_004E94A0[(u32)j];
                    MenuObjSlotsReleaseByKey_3857b0((s32)D_004832D8, p);
                    D_004833B0 = (*pp)->m180;
                    MemStackReset_14d830(D_004832A8 + j * 0x58);
                    MenuObjTeardown_387d60(*pp);
                    MenuObjReset_387dc0(*pp);
                    *pp = 0;
                }
            }
            MenuObjLoopSoundUpdate_3843d0(&D_004832A0);
            D_0048339C = InsectBreedCreate_3cf0c0(sys);
            InsectRecClearPairEntries_3cf2f0(sys);
            InsectRecRemoveMsgsOfKind_3ceed0(sys, 2);
            InsectCharaPathFormat_390de0(buf110, D_0048339C, 0, 0);
            LoadHandleInit_28b610(D_004832E4);
            LoadHandleRequestFile_28b550(D_004832E4, buf110, 1, 0);
            D_0047FBD8++;
        }
        break;
    case 5:
        if (LoadHandleGetStatus_28b2e0(D_004832E4) == 1) {
            r = LoadHandleGetData_28b270(D_004832E4, &sp15C);
            sp158 = -1;
            c = MenuObjFindFree_390d80(&sp158);
            if (c != 0) {
                MenuObjReset_387dc0(c);
                MenuObjLoadFromCfg_387930(c, r, sp158 + 0x263, D_004832A8 + sp158 * 0x58, D_0048339C);
                MenuObjBuildRandomRoute_3871a0(c, &D_004832B8, 4);
                if (c->m984 == 0) {
                    ((f32 *)&D_004833B0)[1] = 2.0f;
                } else {
                    ((f32 *)&D_004833B0)[1] = 6.0f;
                }
                ModelSetPos_151110(c, &D_004833B0);
                h = InsectCageGetCollTris_389d70(&sp154);
                for (i = 0; i < 6; i++) {
                    MenuObjWalkUpdateMaybe_387390(c, h, sp154);
                }
            }
            D_004833A0 = c;
            LoadHandleFree_28b230(D_004832E4);
            InsectCageMenuBuildObjList_3909a0();
            for (i = 0; i < 5; i++) {
                p = D_004E94A0[i];
                if (p != 0 && p->m96C == D_0048339C) {
                    UiEntryListFindDataByTag_28ec30(D_004E94E0, 0x7531)->m10 = (s16)i;
                    BitArraySetReturnOld_384360((u8 *)D_004833A0 + 0x986, 7, 1);
                    break;
                }
            }
            MenuFadeStartFromColor_2a0020(D_00482374);
            D_004833C4 = 5;
            D_0047FBD8++;
        }
        break;
    case 6:
        f = D_0047D2A8;
        if (D_004833C4 > 0) {
            if (--D_004833C4 == 0) {
                scn = D_004832D8;
                cur = D_004833A0;
                MenuObjSlotClear_384990(&scn->m39B0);
                scn->m39B0 = cur;
                MotionListResetAll_171e00(scn->m3BB0);
                ObjGetAttachNodePos_1adec0(cur, 0, buf50);
                ModelSetPos_151110(scn->m39C0, buf50);
                ModelObjPlayMotionByName_1867a0(scn->m39C0, D_00464100, 6);
                ((Obj39C0 *)scn->m39C0)->v44(D_0047D34C);
                InsectCageSePlay_3844b0(&D_004832A0, 8);
            }
        } else if (0.5f < ModelObjGetMotionPhase_1add70(D_004832D8->m39C0)) {
            if (D_004833A0 != 0) {
                BitArraySetReturnOld_384360((u8 *)D_004833A0 + 0x986, 7, 0);
            }
            D_0047FBD8++;
        }
        break;
    case 7:
        if (MotionListIsFinished_171d90(D_004832D8->m3BB0, -1) != 0) {
            MsgFormatParamsCtor_28aa00(buf60);
            MsgFormat_28a9a0(D_00483304 + 0x800, (void *)InsectCageMenuMsgLookup_389d30(0x4E2), buf60, 1);
            UiFitCenterWindow_388270(0x75DA, 1);
            UiSetWidgetsVisibleById_291110(arg1, 0x75DA, 1, 1);
            InsectCageSePlay_3844b0(&D_004832A0, 5);
            D_0047FBD8++;
        }
        break;
    case 8:
        if (PadIsTriggered_1839f0(D_004B2570, 0x60) != 0) {
            PlayMenuSe_289ef0(5);
            MenuFadeSetColor_29ff90(D_00482374, 8, 8, 8);
            MenuFadeSetColor_29ff90(D_00482374, 0, 0, 0);
            InsectCageMenuSetStateFlagMaybe_390aa0(1, 0);
            for (i = 0; i < 5; i++) {
                pp = &D_004E94A0[i];
                if (*pp != 0) {
                    BitArraySetReturnOld_384360((u8 *)*pp + 0x986, 8, 0);
                    BitArraySetReturnOld_384360((u8 *)*pp + 0x986, 7, 0);
                }
            }
            UiSetWidgetsVisibleById_291110(arg1, 0x75DA, 0, 1);
            MenuCursorObjSetVisible_386280(D_004E94C0, 1);
            InsectCageMenuSelectEntry_390d40(0x7531, 0);
        }
        break;
    }
    MenuFadeStep_29ffd0(D_00482374, f);
    return 1;
}
