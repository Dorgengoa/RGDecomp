#include "types.h"

/* A branch-free STATIC INITIALISER (the IosBaseInitCtor_102bd0 / RegisterGlobalObject_100dc0 family).
   Drafted by build/rk_ctor.py: m2c gives the order and the arguments, the
   listing gives each global's RELOCATION -- %gp_rel means a plain extern,
   %hi/%lo means an incomplete array, because a written global cannot take
   the `const` escape out of small data. */

extern void ConstructArray_100620(void *, void *, s32, s32, s32);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void IosBaseInitCtor_102bd0(void *);
extern void WIosBaseInitCtor_103110(void *);
extern void MemStackCtor_14e030(void *);
extern void LightningMgrCtorMaybe_2d6490(void *);
extern void LightningMgrReset_2d71e0(void *);
extern void EffectMgrCtor_2e33b0(void *);
extern void StatusEffectReset_33c050(void *);
extern void IosBaseInitDtor_102ee0(void);
extern void WIosBaseInitDtor_103420(void);
extern void MovingLineCtor_2d9060(void);
extern void BladeLineCtor_2d9090(void);
extern void EffectTimedSlotCtor_2d90c0(void);
extern void GuardEffectCtor_2d90f0(void);
extern void EffectMgrDtor_2e32a0(void);

extern s32 D_00482658;
extern s32 D_00482664;
extern s32 D_00482668;
extern s32 D_00482674;
extern s32 D_00482678;
extern s32 D_004826B0;
extern u8 D_004DCCF0[];
extern u8 D_004DCD50[];
extern u8 D_004E0DD0[];
extern u8 D_004E39D0[];
extern u8 D_004E3A90[];
extern u8 D_004E4190[];
extern u8 D_004E6110[];

void StaticInitEffectGlobals_46c370(void)
{
    IosBaseInitCtor_102bd0(&D_00482664);
    RegisterGlobalObject_100dc0(&D_00482664, IosBaseInitDtor_102ee0, &D_00482658);
    WIosBaseInitCtor_103110(&D_00482674);
    RegisterGlobalObject_100dc0(&D_00482674, WIosBaseInitDtor_103420, &D_00482668);
    MemStackCtor_14e030(D_004DCCF0);
    EffectMgrCtor_2e33b0(D_004DCD50);
    RegisterGlobalObject_100dc0(D_004DCD50, EffectMgrDtor_2e32a0, &D_00482678);
    ConstructArray_100620(D_004E0DD0, GuardEffectCtor_2d90f0, 0, 0x340, 0xC);
    ConstructArray_100620(D_004E39D0, EffectTimedSlotCtor_2d90c0, 0, 0x10, 0xC);
    ConstructArray_100620(D_004E3A90, BladeLineCtor_2d9090, 0, 0x70, 0x10);
    ConstructArray_100620(D_004E4190, MovingLineCtor_2d9060, 0, 0x150, 0x18);
    LightningMgrCtorMaybe_2d6490(D_004E6110);
    LightningMgrReset_2d71e0(D_004E6110);
    StatusEffectReset_33c050(&D_004826B0);
}
