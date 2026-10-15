#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void MemStackCtor_14e030(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482748;
extern s32 D_00482754;
extern s32 D_00482758;
extern s32 D_00482764;
extern u8 D_004E6420[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitDrawWorkHeap_46c5d0(void)
{
    IosBaseInitCtor_102bd0(&D_00482754);
    RegisterGlobalObject_100dc0(&D_00482754, IosBaseInitDtor_102ee0, &D_00482748);
    WIosBaseInitCtor_103110(&D_00482764);
    RegisterGlobalObject_100dc0(&D_00482764, WIosBaseInitDtor_103420, &D_00482758);
    MemStackCtor_14e030(D_004E6420);
}
