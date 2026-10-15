#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void SysMsgInit_1c69e0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481530;
extern s32 D_0048153C;
extern s32 D_00481540;
extern s32 D_0048154C;
extern u8 D_004A3EF0[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitSysMsg_4698d0(void)
{
    IosBaseInitCtor_102bd0(&D_0048153C);
    RegisterGlobalObject_100dc0(&D_0048153C, IosBaseInitDtor_102ee0, &D_00481530);
    WIosBaseInitCtor_103110(&D_0048154C);
    RegisterGlobalObject_100dc0(&D_0048154C, WIosBaseInitDtor_103420, &D_00481540);
    SysMsgInit_1c69e0(D_004A3EF0);
}
