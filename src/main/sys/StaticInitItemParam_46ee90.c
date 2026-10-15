#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004654B0;
extern const s32 D_00467818;
extern s32 D_00480050;
extern s32 D_00483D08;
extern s32 D_00483D14;
extern s32 D_00483D18;
extern s32 D_00483D24;
extern s32 D_00483D40;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitItemParam_46ee90(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483D14);
    RegisterGlobalObject_100dc0(&D_00483D14, IosBaseInitDtor_102ee0, &D_00483D08);
    WIosBaseInitCtor_103110(&D_00483D24);
    RegisterGlobalObject_100dc0(&D_00483D24, WIosBaseInitDtor_103420, &D_00483D18);
    t0 = D_00480050;
    t1 = D_004654B0;
    D_00483D40 = t0;
    *(s32 *)&D_00467818 = t1;
}
