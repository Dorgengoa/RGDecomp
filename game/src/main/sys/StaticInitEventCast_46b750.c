/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitEventCast_46b750 1
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

extern s32 D_00481F08;
extern s32 D_00481F14;
extern s32 D_00481F18;
extern s32 D_00481F24;
extern s32 D_00481F48;
extern s32 D_00481F4C;
extern s32 D_00481F50;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitEventCast_46b750(void)
{
    IosBaseInitCtor_102bd0(&D_00481F14);
    RegisterGlobalObject_100dc0(&D_00481F14, IosBaseInitDtor_102ee0, &D_00481F08);
    WIosBaseInitCtor_103110(&D_00481F24);
    RegisterGlobalObject_100dc0(&D_00481F24, WIosBaseInitDtor_103420, &D_00481F18);
    D_00481F48 = 0;
    D_00481F50 = 0;
    D_00481F4C = 0;
}
