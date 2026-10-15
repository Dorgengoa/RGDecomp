#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004822F0;
extern s32 D_004822FC;
extern s32 D_00482300;
extern s32 D_0048230C;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitIosInit_46be60(void)
{
    IosBaseInitCtor_102bd0(&D_004822FC);
    RegisterGlobalObject_100dc0(&D_004822FC, IosBaseInitDtor_102ee0, &D_004822F0);
    WIosBaseInitCtor_103110(&D_0048230C);
    RegisterGlobalObject_100dc0(&D_0048230C, WIosBaseInitDtor_103420, &D_00482300);
}
