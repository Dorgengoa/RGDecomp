#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004818B8;
extern s32 D_004818C4;
extern s32 D_004818C8;
extern s32 D_004818D4;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitIosInit_46a360(void)
{
    IosBaseInitCtor_102bd0(&D_004818C4);
    RegisterGlobalObject_100dc0(&D_004818C4, IosBaseInitDtor_102ee0, &D_004818B8);
    WIosBaseInitCtor_103110(&D_004818D4);
    RegisterGlobalObject_100dc0(&D_004818D4, WIosBaseInitDtor_103420, &D_004818C8);
}
