#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004654E8;
extern const s32 D_004671B8;
extern s32 D_0048006C;
extern s32 D_00483B38;
extern s32 D_00483B44;
extern s32 D_00483B48;
extern s32 D_00483B54;
extern s32 D_00483B58;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitBtlStsParam_46e990(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483B44);
    RegisterGlobalObject_100dc0(&D_00483B44, IosBaseInitDtor_102ee0, &D_00483B38);
    WIosBaseInitCtor_103110(&D_00483B54);
    RegisterGlobalObject_100dc0(&D_00483B54, WIosBaseInitDtor_103420, &D_00483B48);
    t0 = D_0048006C;
    t1 = D_004654E8;
    D_00483B58 = t0;
    *(s32 *)&D_004671B8 = t1;
}
