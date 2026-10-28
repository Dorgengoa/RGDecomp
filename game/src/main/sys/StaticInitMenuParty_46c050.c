/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitMenuParty_46c050 1
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

extern s32 D_00482518;
extern s32 D_00482524;
extern s32 D_00482528;
extern s32 D_00482534;
extern u8 D_004DB730[];
extern u8 D_004DB760[];
extern u8 D_004DB790[];
extern u8 D_004DB7C0[];
extern u8 D_004DB7F0[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitMenuParty_46c050(void)
{
    IosBaseInitCtor_102bd0(&D_00482524);
    RegisterGlobalObject_100dc0(&D_00482524, IosBaseInitDtor_102ee0, &D_00482518);
    WIosBaseInitCtor_103110(&D_00482534);
    RegisterGlobalObject_100dc0(&D_00482534, WIosBaseInitDtor_103420, &D_00482528);
    UiSelFrameReset_28db70(D_004DB730);
    UiSelFrameReset_28db70(D_004DB760);
    UiSelFrameReset_28db70(D_004DB790);
    UiSelFrameReset_28db70(D_004DB7C0);
    UiSelFrameReset_28db70(D_004DB7F0);
}
