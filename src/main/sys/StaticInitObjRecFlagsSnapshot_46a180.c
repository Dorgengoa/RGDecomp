#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481818;
extern s32 D_00481824;
extern s32 D_00481828;
extern s32 D_00481834;
extern u8 D_004B3370[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitObjRecFlagsSnapshot_46a180(void)
{
    s32 l4;
    s32 l5;
    s32 l6;

    IosBaseInitCtor_102bd0(&D_00481824);
    RegisterGlobalObject_100dc0(&D_00481824, IosBaseInitDtor_102ee0, &D_00481818);
    WIosBaseInitCtor_103110(&D_00481834);
    RegisterGlobalObject_100dc0(&D_00481834, WIosBaseInitDtor_103420, &D_00481828);
    l4 = 0;
    do {
        l5 = (((l4 << 3) - l4) << 2);
        l6 = 0;
        do {
            D_004B3370[(((l4 << 3) - l4) << 2) + l6 + 1] = 0;
            l5 = ((l6 + 1) < 0x1C);
            l6 = (l6 + 1);
        } while (l5 != 0);
        l4 = (l4 + 1);
    } while (l4 < 8);
    D_004B3370[0] = 0;
}
