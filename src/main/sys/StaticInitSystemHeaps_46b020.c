#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void MemStackCtor_14e030(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481B38;
extern s32 D_00481B44;
extern s32 D_00481B48;
extern s32 D_00481B54;
extern u8 D_004BB830[];
extern u8 D_004BB890[];
extern u8 D_004BB8F0[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitSystemHeaps_46b020(void)
{
    IosBaseInitCtor_102bd0(&D_00481B44);
    RegisterGlobalObject_100dc0(&D_00481B44, IosBaseInitDtor_102ee0, &D_00481B38);
    WIosBaseInitCtor_103110(&D_00481B54);
    RegisterGlobalObject_100dc0(&D_00481B54, WIosBaseInitDtor_103420, &D_00481B48);
    MemStackCtor_14e030(D_004BB830);
    MemStackCtor_14e030(D_004BB890);
    MemStackCtor_14e030(D_004BB8F0);
}
