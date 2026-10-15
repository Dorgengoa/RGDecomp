#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_00465638;
extern const s32 D_00468180;
extern s32 D_00480120;
extern s32 D_00483EE8;
extern s32 D_00483EF4;
extern s32 D_00483EF8;
extern s32 D_00483F04;
extern s32 D_00483F08;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitShopParam_46f490(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483EF4);
    RegisterGlobalObject_100dc0(&D_00483EF4, IosBaseInitDtor_102ee0, &D_00483EE8);
    WIosBaseInitCtor_103110(&D_00483F04);
    RegisterGlobalObject_100dc0(&D_00483F04, WIosBaseInitDtor_103420, &D_00483EF8);
    t0 = D_00480120;
    t1 = D_00465638;
    D_00483F08 = t0;
    *(s32 *)&D_00468180 = t1;
}
