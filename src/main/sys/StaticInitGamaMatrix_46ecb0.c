#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004655F8;
extern const s32 D_004675E0;
extern s32 D_004800F8;
extern s32 D_00483C58;
extern s32 D_00483C64;
extern s32 D_00483C68;
extern s32 D_00483C74;
extern s32 D_00483C88;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitGamaMatrix_46ecb0(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483C64);
    RegisterGlobalObject_100dc0(&D_00483C64, IosBaseInitDtor_102ee0, &D_00483C58);
    WIosBaseInitCtor_103110(&D_00483C74);
    RegisterGlobalObject_100dc0(&D_00483C74, WIosBaseInitDtor_103420, &D_00483C68);
    t0 = D_004800F8;
    t1 = D_004655F8;
    D_00483C88 = t0;
    *(s32 *)&D_004675E0 = t1;
}
