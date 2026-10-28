/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitTextEntryResMaybe_46f910 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004802D4;
extern s32 D_004840E0;
extern s32 D_004840EC;
extern s32 D_004840F0;
extern s32 D_004840FC;
extern s32 D_00484100;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitTextEntryResMaybe_46f910(void)
{
    s32 t0;

    IosBaseInitCtor_102bd0(&D_004840EC);
    RegisterGlobalObject_100dc0(&D_004840EC, IosBaseInitDtor_102ee0, &D_004840E0);
    WIosBaseInitCtor_103110(&D_004840FC);
    RegisterGlobalObject_100dc0(&D_004840FC, WIosBaseInitDtor_103420, &D_004840F0);
    t0 = D_004802D4;
    D_00484100 = t0;
}
