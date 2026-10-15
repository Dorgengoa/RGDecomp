#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void HatenaMarkListCtor_3450d0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482DB0;
extern s32 D_00482DBC;
extern s32 D_00482DC0;
extern s32 D_00482DCC;
extern s32 D_00482DD0;
extern s32 D_00482DE0;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];
extern u8 HatenaMarkListDtor_345080[];

void StaticInitHatenaMark_46d420(void)
{
    IosBaseInitCtor_102bd0(&D_00482DBC);
    RegisterGlobalObject_100dc0(&D_00482DBC, IosBaseInitDtor_102ee0, &D_00482DB0);
    WIosBaseInitCtor_103110(&D_00482DCC);
    RegisterGlobalObject_100dc0(&D_00482DCC, WIosBaseInitDtor_103420, &D_00482DC0);
    HatenaMarkListCtor_3450d0(&D_00482DE0);
    RegisterGlobalObject_100dc0(&D_00482DE0, HatenaMarkListDtor_345080, &D_00482DD0);
}
