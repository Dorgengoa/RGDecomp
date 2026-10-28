/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitInsectBattle_46ce20 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482AD0;
extern s32 D_00482ADC;
extern s32 D_00482AE0;
extern s32 D_00482AEC;
extern u8 D_004E7FB0[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitInsectBattle_46ce20(void)
{
    IosBaseInitCtor_102bd0(&D_00482ADC);
    RegisterGlobalObject_100dc0(&D_00482ADC, IosBaseInitDtor_102ee0, &D_00482AD0);
    WIosBaseInitCtor_103110(&D_00482AEC);
    RegisterGlobalObject_100dc0(&D_00482AEC, WIosBaseInitDtor_103420, &D_00482AE0);
    MemStackCtor_14e030(D_004E7FB0);
}
