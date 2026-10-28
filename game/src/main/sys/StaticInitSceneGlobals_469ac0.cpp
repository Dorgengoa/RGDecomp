#include "types.h"

class Big {
    u8 pad[0x4394];
public:
    VC_VPTR_MEMBER;
    void v0C() { VCM0(void, 0xC); }
};

extern "C" {
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void IosBaseInitCtor_102bd0(void *);
extern void WIosBaseInitCtor_103110(void *);
extern void MemStackCtor_14e030(void *);
extern void CBlurTexCtor_179330(void *);
extern void PadCtor_185040(void *);
extern void SoundSlotCtor_1c6dd0(u32);
extern void SoundNoteListCtor_1c6e00(void *);
extern void SoundCategoryFadeCtor_1c6e30(void *);
extern void SceneInfoBlockCtorMaybe_1c6e60(void *);
extern void ParticleSwirlCtor_1c6e90(void *);
extern void ScreenFadeBlockCtor_1c6f00(void *);
extern void DofParamsCtor_1c6f30(void *);
extern void DoorGlareParamsCtor_1c6f80(void *);
extern void CBlurParamsCtor_1c6fb0(void *);
extern void SceneCtor_1c6fe0(void *);
extern u8 D_00471210[];
extern u8 D_00481608;
extern u8 D_00481614;
extern u8 D_00481618;
extern u8 D_00481624;
extern u8 D_004A6FA0[];
extern u8 D_004A7000[];
extern void *D_004AB394[];
extern u8 D_004AC8A0[];
extern u8 D_004AC8C0[];
extern u8 D_004AC934[];
extern u8 D_004AC96C[];
extern u8 D_004AC980[];
extern u8 D_004AC9E0[];
extern u8 D_004ACD00[];
extern u8 D_004B1E20[];
extern u8 D_004B20A4[];
extern u8 D_004B20B0[];
extern u8 D_004B2468[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];
extern void IosBaseInitDtor_102ee0(void);
extern void WIosBaseInitDtor_103420(void);

}

extern "C" void StaticInitSceneGlobals_469ac0(void)
{
    u8 *var_16;

    IosBaseInitCtor_102bd0(&D_00481614);
    RegisterGlobalObject_100dc0(&D_00481614, (void *)IosBaseInitDtor_102ee0, &D_00481608);
    WIosBaseInitCtor_103110(&D_00481624);
    RegisterGlobalObject_100dc0(&D_00481624, (void *)WIosBaseInitDtor_103420, &D_00481618);
    MemStackCtor_14e030(D_004A6FA0);
    SceneCtor_1c6fe0(D_004A7000);
    D_004AB394[0] = D_00471210;
    CBlurParamsCtor_1c6fb0(D_004AC8A0);
    CBlurTexCtor_179330(D_004AC8C0);
    DoorGlareParamsCtor_1c6f80(D_004AC934);
    DofParamsCtor_1c6f30(D_004AC96C);
    ScreenFadeBlockCtor_1c6f00(D_004AC980);
    ParticleSwirlCtor_1c6e90(D_004AC9E0);
    SceneInfoBlockCtorMaybe_1c6e60(D_004ACD00);
    SoundCategoryFadeCtor_1c6e30(D_004B1E20);
    SoundNoteListCtor_1c6e00(D_004B20A4);
    var_16 = D_004B20B0;
    do {
        SoundSlotCtor_1c6dd0((u32)var_16);
        var_16 += 0x88;
    } while (var_16 < D_004B2468);
    ((Big *)D_004A7000)->v0C();
    PadCtor_185040(D_004B2570);
    PadCtor_185040(D_004B27E0);
}
