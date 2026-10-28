/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitIosInit_46d160 1
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

extern s32 D_00482C50;
extern s32 D_00482C5C;
extern s32 D_00482C60;
extern s32 D_00482C6C;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitIosInit_46d160(void)
{
    IosBaseInitCtor_102bd0(&D_00482C5C);
    RegisterGlobalObject_100dc0(&D_00482C5C, IosBaseInitDtor_102ee0, &D_00482C50);
    WIosBaseInitCtor_103110(&D_00482C6C);
    RegisterGlobalObject_100dc0(&D_00482C6C, WIosBaseInitDtor_103420, &D_00482C60);
}
