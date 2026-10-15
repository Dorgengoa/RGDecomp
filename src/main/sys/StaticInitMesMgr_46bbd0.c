#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void MesWinCtor_276ef0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482130;
extern s32 D_0048213C;
extern s32 D_00482140;
extern s32 D_0048214C;
extern u8 D_004D5980[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitMesMgr_46bbd0(void)
{
    IosBaseInitCtor_102bd0(&D_0048213C);
    RegisterGlobalObject_100dc0(&D_0048213C, IosBaseInitDtor_102ee0, &D_00482130);
    WIosBaseInitCtor_103110(&D_0048214C);
    RegisterGlobalObject_100dc0(&D_0048214C, WIosBaseInitDtor_103420, &D_00482140);
    MesWinCtor_276ef0(D_004D5980);
}
