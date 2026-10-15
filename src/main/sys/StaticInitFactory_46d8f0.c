#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void MemStackCtor_14e030(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004830C8;
extern s32 D_004830D4;
extern s32 D_004830D8;
extern s32 D_004830E4;
extern u8 D_004E9020[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitFactory_46d8f0(void)
{
    IosBaseInitCtor_102bd0(&D_004830D4);
    RegisterGlobalObject_100dc0(&D_004830D4, IosBaseInitDtor_102ee0, &D_004830C8);
    WIosBaseInitCtor_103110(&D_004830E4);
    RegisterGlobalObject_100dc0(&D_004830E4, WIosBaseInitDtor_103420, &D_004830D8);
    MemStackCtor_14e030(D_004E9020);
}
