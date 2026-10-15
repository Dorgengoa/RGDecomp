#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void ScriptVmCtor_176be0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F58;
extern s32 D_00481F64;
extern s32 D_00481F68;
extern s32 D_00481F74;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];
extern u8 gSystemVm[];

void StaticInitSystemVm_46b7b0(void)
{
    IosBaseInitCtor_102bd0(&D_00481F64);
    RegisterGlobalObject_100dc0(&D_00481F64, IosBaseInitDtor_102ee0, &D_00481F58);
    WIosBaseInitCtor_103110(&D_00481F74);
    RegisterGlobalObject_100dc0(&D_00481F74, WIosBaseInitDtor_103420, &D_00481F68);
    ScriptVmCtor_176be0(gSystemVm);
}
