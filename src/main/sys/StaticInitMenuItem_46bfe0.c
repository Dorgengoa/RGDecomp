#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void MemStackCtor_14e030(void *);
extern void UiSelFrameReset_28db70(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482468;
extern s32 D_00482474;
extern s32 D_00482478;
extern s32 D_00482484;
extern u8 D_004DB3D0[];
extern u8 D_004DB430[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitMenuItem_46bfe0(void)
{
    IosBaseInitCtor_102bd0(&D_00482474);
    RegisterGlobalObject_100dc0(&D_00482474, IosBaseInitDtor_102ee0, &D_00482468);
    WIosBaseInitCtor_103110(&D_00482484);
    RegisterGlobalObject_100dc0(&D_00482484, WIosBaseInitDtor_103420, &D_00482478);
    MemStackCtor_14e030(D_004DB3D0);
    UiSelFrameReset_28db70(D_004DB430);
}
