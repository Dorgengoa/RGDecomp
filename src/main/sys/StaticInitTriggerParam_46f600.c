#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004654A8;
extern const s32 D_004682F0;
extern s32 D_0048004C;
extern s32 D_00483F70;
extern s32 D_00483F7C;
extern s32 D_00483F80;
extern s32 D_00483F8C;
extern s32 D_00483F90;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitTriggerParam_46f600(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483F7C);
    RegisterGlobalObject_100dc0(&D_00483F7C, IosBaseInitDtor_102ee0, &D_00483F70);
    WIosBaseInitCtor_103110(&D_00483F8C);
    RegisterGlobalObject_100dc0(&D_00483F8C, WIosBaseInitDtor_103420, &D_00483F80);
    t0 = D_0048004C;
    t1 = D_004654A8;
    D_00483F90 = t0;
    *(s32 *)&D_004682F0 = t1;
}
