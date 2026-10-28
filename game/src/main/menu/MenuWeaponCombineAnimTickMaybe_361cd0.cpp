#include "types.h"
#pragma divbyzerocheck on

typedef struct Ctx361 {
    u8 pad0[0x5C];
    s32 m5C;
    u8 m60;
    u8 m61;
    u8 pad62[0x70 - 0x62];
    s32 m70;
    u8 pad74[0x78 - 0x74];
    s32 m78;
    s32 m7C;
    u8 m80;
    u8 m81;
    u8 pad82[0x84 - 0x82];
    s32 m84;
    u8 pad88[0x8C - 0x88];
    s32 m8C;
    u8 pad90[0x94 - 0x90];
    s8 m94;
    s8 m95;
    s8 m96;
} Ctx361;

typedef struct Info361 {
    u8 pad0[0x1C];
    s32 m1C;
    u8 pad20[0xB8 - 0x20];
} Info361;

typedef struct Sys361 {
    u8 pad0[0x2C];
    s32 m2C;
    s32 m30;
} Sys361;

typedef struct Chr361 {
    u8 pad0[0x18];
    s32 m18;
} Chr361;

typedef struct Ent361 {
    u8 pad0[6];
    s16 m6;
} Ent361;

class VObj361 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v60() { return VCM0(s32, 0x60); }
};

extern "C" {
extern s32 MotionListIsFinished_171d90(s32, s32);
extern void MotionListResetAll_171e00(s32);
extern void ModelObjPlayMotionByName_1867a0(s32, void *, s32);
extern void SoundStopEntry_1b8bc0(s32, s32, s32);
extern void SoundPlayDefault_1b9ae0(s32, s32, s32);
extern void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);
extern s32 GetLoaderMgr_1f59d0(void);
extern Chr361 *GetGameData_1fede0(void);
extern void EventVoicePlayLine_2071b0(s32, s32, s32, f32);
extern void MsgFormat_28a9a0(void *, s32, void *, s32);
extern void MsgFormatParamsCtor_28aa00(void *);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, void *, s32);
extern Ent361 *MenuGetSelItem_2a02d0(Sys361 *);
extern void MenuWeaponCombineGridHighlightMatchingMaybe_361640(Ctx361 *, s32);
extern void MenuWeaponCombineGridRefreshMaybe_3619d0(Ctx361 *, s32);
extern void MenuWeaponCombineShowMsg_362490(Ctx361 *, s32, s32);
extern s32 WeaponCombinePerformMaybe_3c36c0(s32, s32, u8 *, u8 *, s32 *);
extern s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern VObj361 *ItemFindOwnerChara_3d4d80(s32, s32);
extern u8 D_00462D40[];
extern u8 D_00462D60[];
extern u8 D_00462D78[];
extern u8 D_00462D88[];
extern s32 D_004659F0[];
extern Sys361 *D_00482374;
extern s32 D_004823D0;
extern s32 D_004823D8;
extern s32 D_004823E4;
extern u8 D_00483060;
extern u8 D_00483068;
extern u8 D_0048306C;
extern u8 D_00483074;
extern s32 D_00483078;
extern u8 D_004E8FA0[];
}

extern "C" s32 MenuWeaponCombineAnimTickMaybe_361cd0(Ctx361 *arg0)
{
    u8 sp11F;
    u8 sp11E;
    s32 sp118;
    Info361 info __attribute__((aligned(16)));
    s32 r;
    s32 t;
    s32 n;
    s32 id;
    s16 k;
    f32 one;
    Ent361 *e;
    Chr361 *c;
    VObj361 *o;

    r = 0;
    if (arg0->m60 == 0) {
        return 0;
    }
    if (arg0->m61 == 5) {
        if (++D_00483078 == 0x2A) {
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x3FC), 0);
            e = MenuGetSelItem_2a02d0(D_00482374);
            if (e != 0) {
                id = e->m6;
                sp11F = 0;
                sp11E = 0;
                sp118 = 0;
                arg0->m7C = WeaponCombinePerformMaybe_3c36c0(GetGameData_1fede0()->m18, id, &sp11F, &sp11E, &sp118);
                arg0->m70 = 0;
                if (sp11F != 0) {
                    arg0->m70 = 1;
                }
                arg0->m80 = 1;
                SoundPlayDefault_1b9ae0(D_004823E4, 5, 0);
                arg0->m78 = 0;
            }
        }
    }
    if (arg0->m61 == 4 || arg0->m61 == 7) {
        r = 7;
        if (++D_00483078 == 0x3C) {
            MenuWeaponCombineGridRefreshMaybe_3619d0(arg0, 1);
            arg0->m61 = 8;
            SoundPlayDefault_1b9ae0(D_004823E4, 4, 0);
            arg0->m78 = 0;
            return 3;
        }
    }
    if (MotionListIsFinished_171d90(D_004823D0 + 0x1F0, -1) != 0) {
        switch (arg0->m61) {
        case 0:
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D40, 4);
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x3FA), 0);
            arg0->m60 = 0;
            MenuWeaponCombineGridHighlightMatchingMaybe_361640(arg0, 1);
            arg0->m94 = 2;
            r = 1;
            arg0->m95 = 6;
            arg0->m96 = 2;
            break;
        case 1:
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D60, 6);
            arg0->m61 = 6;
            arg0->m78 = 0;
            break;
        case 6:
            MotionListResetAll_171e00(D_004823D0 + 0x1F0);
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D60, 6);
            arg0->m78 = 0;
            break;
        case 2:
            if (arg0->m78 < 8) {
                MotionListResetAll_171e00(D_004823D0 + 0x1F0);
                ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D60, 6);
            }
            t = arg0->m78 + 1;
            arg0->m78 = t;
            if (t == 4) {
                if (D_00483068 != 0 || D_0048306C != 0 || D_00483074 != 0) {
                    n = 0x419;
                    if (D_0048306C != 0) {
                        n = 0x41F;
                    }
                    if (D_00483074 != 0) {
                        arg0->m5C = 0;
                        n = 0x421;
                    }
                    MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, n), 0);
                    UiSetTextString_28f510(arg0->m84, 0x21E, (void *)MsgTableLookup_28aa30(D_004823D8, 0x418), 0);
                    arg0->m61 = 6;
                    StateMachineSetState_28ede0(arg0->m8C, 0x28, 0);
                } else if (D_00483060 != 0) {
                    if (arg0->m81 == 0) {
                        MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x40E), 0);
                        n = D_00482374->m30;
                        c = GetGameData_1fede0();
                        MsgFormatParamsCtor_28aa00(&info);
                        id = D_00482374->m2C;
                        o = ItemFindOwnerChara_3d4d80(InvFindByCategoryIndex_3c86e0(c->m18, 0, id, n % D_004659F0[0], n / D_004659F0[0], 0), 0);
                        info.m1C = o->v60();
                        MsgFormat_28a9a0(D_004E8FA0, MsgTableLookup_28aa30(D_004823D8, 0x40F), &info, 1);
                        UiSetTextString_28f510(arg0->m84, 0x21E, D_004E8FA0, 0);
                        arg0->m61 = 6;
                    } else {
                        MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x415), 0);
                        arg0->m61 = 6;
                    }
                    StateMachineSetState_28ede0(arg0->m8C, 0x28, 0);
                } else {
                    MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x3FB), 0);
                    SoundPlayDefault_1b9ae0(D_004823E4, 7, 0);
                }
            } else if (t > 7) {
                SoundStopEntry_1b8bc0(D_004823E4, 8, 0);
                ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D78, 6);
                arg0->m80 = 0;
                arg0->m5C = 0x78;
                arg0->m61 = 5;
                arg0->m78 = 0;
                D_00483078 = 0;
            }
            break;
        case 7:
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D78, 6);
            D_00483078 = 0;
            break;
        case 8:
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D88, 0);
            MenuWeaponCombineGridRefreshMaybe_3619d0(arg0, 1);
            arg0->m80 = 0;
            arg0->m81 = 0;
            arg0->m60 = 0;
            arg0->m95 = 1;
            arg0->m96 = 0;
            D_00483078 = 0;
            break;
        case 4:
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D88, 0);
            D_00483078 = 0;
            break;
        case 5:
            if (arg0->m78 <= 0) {
                ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D88, 0);
            }
            t = arg0->m78 + 1;
            arg0->m78 = t;
            if (t > 1) {
                k = 0x3FD;
                if (arg0->m70 != 0) {
                    k = 0x411;
                    EventVoicePlayLine_2071b0(2, 0xAA, 0xE2, 1.0f);
                } else {
                    EventVoicePlayLine_2071b0(2, 0xAA, 0xE1, 1.0f);
                }
                MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, k), 0);
                StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0xF, 1.0f);
                MenuWeaponCombineGridRefreshMaybe_3619d0(arg0, 1);
                arg0->m60 = 0;
                arg0->m95 = 1;
                r = 2;
                arg0->m96 = 2;
                arg0->m5C = 0x78;
                arg0->m70 = 0;
                arg0->m78 = 0;
            }
            break;
        case 3:
            t = arg0->m78 + 1;
            arg0->m78 = t;
            if (t > 6) {
                ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D88, 0);
                arg0->m60 = 0;
            }
            break;
        }
    }
    return r;
}
