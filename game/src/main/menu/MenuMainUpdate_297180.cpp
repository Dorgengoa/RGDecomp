/* rgp:protos */
#line 1
#include "types.h"
typedef rg_u128 u128;

struct ObjC0_B { u8 pad[0xC0]; };
struct ObjC0 : ObjC0_B {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void fC8(f32 a0) { VCM(void, (void *, f32), 0xC8, a0); }
    u8 padC4[0x1C];
    u128 mE0;
    u128 mF0;
};
struct ObjD0_B { u8 pad[0x1B0]; };
struct ObjD0 : ObjD0_B {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f44(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
};

struct Obj74 { u8 pad[0x46]; s16 m46; };

extern "C" s16 D_0047EB98;
extern "C" u128 D_0047EBE0 __attribute__((section(".sdata")));
extern "C" u128 D_0047EBF0 __attribute__((section(".sdata")));
extern "C" Obj74 *D_00482374;
extern "C" s32 D_00482388;
extern "C" s16 D_004823A8;
extern "C" u8 D_004823B4;
extern "C" u8 D_004823CC;
extern "C" ObjD0 *D_004823D0;
extern "C" ObjC0 *D_004823D4;
extern "C" s64 D_00482350;
extern "C" u8 D_004B2570[];
extern "C" u8 D_004DB190[];
extern "C" u8 D_004DB1B0[];
extern "C" u8 D_004DB1D0[];
extern "C" u8 D_004DB220[];
extern "C" u8 D_004DB23B[];
extern "C" u8 D_004DB240[];
extern "C" s32 D_004DB250[];

extern "C" {
f32 UiGetWidgetAlpha_290770(void *, s32);
u8 *GetCurrentScene_1f5be0();
ObjC0 *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
void CameraSetLag_177170(ObjC0 *, f32, f32);
void StateMachineSetState_28ede0(void *, s32, s32);
void MenuMainResLoadStep_298bb0();
s32 ReturnZero_207fe0();
s32 PadIsHeld_183a20(void *, s32);
s32 PadIsTriggered_1839f0(void *, s32);
s32 IsTgsDemoBuild_207f20();
void DebugItemIconGridShow_29a890(void *, s32);
void UiUpdateWidgets_2913a0(void *);
void DebugItemListUpdate_299dc0(void *);
void DebugItemIconGridUpdate_29a2f0(void *);
s32 GetDrawCtxNameTable_15de40();
f32 GetSceneTimeStep_293350();
void TexGroupUpdateAnim_157ca0(s32, s32, f32);
void StateMachineUpdate_28ed70(void *);
void MenuWeaponCombineResultModelUpdate_2a8580();
void MenuMobPreviewViewUpdate_35fc00(s32, int, int, int);
void InsectCageMenuUpdate_38a230();
}

extern "C" void MenuMainUpdate_297180(void)
{
    u8 *w;
    ObjC0 *o;
    s32 h;
    u128 q0;
    u128 q1;

    if (D_004823A8 != 0) {
        if (D_0047EB98 == 1 && !(UiGetWidgetAlpha_290770(D_004DB190, 1) < 1.0f)) {
            w = GetCurrentScene_1f5be0();
            *(s32 *)(w + 0x4348) = *(s32 *)(w + 0x4344);
            *(s32 *)(w + 0x4344) = 4;
            w = GetCurrentScene_1f5be0();
            o = ObjRecGetLiveObject_1c3bc0(w, *(s32 *)(w + 0x4344));
            D_004823D4 = o;
            o->mE0 = D_0047EBE0;
            o->mF0 = D_0047EBF0;
            CameraSetLag_177170(o, 1.0f, -1.0f);
            D_004823D4->fC8(-1.0f);
            D_0047EB98 = 0;
        }
        if (D_004823B4 != 0 && D_0047EB98 == 0) {
            D_004823A8 = 2;
            D_004823B4 = 0;
            StateMachineSetState_28ede0(&D_00482350, 1, 0);
        }
        MenuMainResLoadStep_298bb0();
        if (ReturnZero_207fe0() != 0 && D_004823A8 >= 2) {
            if (PadIsHeld_183a20(D_004B2570, 8) != 0) {
                if (PadIsTriggered_1839f0(D_004B2570, 0x400) != 0 && IsTgsDemoBuild_207f20() == 0 && D_004DB250[0] == 0 && D_004DB23B[0] == 0) {
                    D_004DB23B[0] = 1;
                }
            } else {
                if (PadIsTriggered_1839f0(D_004B2570, 0x400) != 0 && IsTgsDemoBuild_207f20() == 0) {
                    if (D_004DB250[0] == 0 && D_004DB23B[0] == 0) {
                        DebugItemIconGridShow_29a890(D_004DB240, 1);
                    } else if (D_004DB250[0] != 0) {
                        DebugItemIconGridShow_29a890(D_004DB240, 0);
                    } else {
                        D_004DB23B[0] = 0;
                    }
                }
            }
        }
        if (D_004823A8 < 2) {
            UiUpdateWidgets_2913a0(D_004DB190);
        } else {
            DebugItemListUpdate_299dc0(D_004DB220);
            DebugItemIconGridUpdate_29a2f0(D_004DB240);
            if (D_004DB23B[0] == 0 && D_004DB250[0] == 0) {
                h = GetDrawCtxNameTable_15de40();
                if (D_004823CC == 0 && h != 0) {
                    TexGroupUpdateAnim_157ca0(h, 0x32E, GetSceneTimeStep_293350());
                }
                UiUpdateWidgets_2913a0(D_004DB1B0);
                UiUpdateWidgets_2913a0(D_004DB1D0);
                StateMachineUpdate_28ed70(&D_00482350);
            }
        }
        if (D_004823D0 != 0 && D_004823CC != 0) {
            D_004823D0->f44(GetSceneTimeStep_293350() / 2.0f);
        }
        MenuWeaponCombineResultModelUpdate_2a8580();
        if (D_00482388 != 0) {
            MenuMobPreviewViewUpdate_35fc00(D_00482388, 0, 0, 0);
        }
        if (D_00482374 != 0 && D_00482374->m46 != 0) {
            InsectCageMenuUpdate_38a230();
        }
    }
}
