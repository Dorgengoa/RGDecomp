/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitInsectMenu_46de40 1
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

extern s32 D_0047FF58;
extern s32 D_0047FF5C;
extern s32 D_004802D0;
extern s32 D_004834C8;
extern s32 D_004834D4;
extern s32 D_004834D8;
extern s32 D_004834E4;
extern s32 D_00483538;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitInsectMenu_46de40(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_004834D4);
    RegisterGlobalObject_100dc0(&D_004834D4, IosBaseInitDtor_102ee0, &D_004834C8);
    WIosBaseInitCtor_103110(&D_004834E4);
    RegisterGlobalObject_100dc0(&D_004834E4, WIosBaseInitDtor_103420, &D_004834D8);
    t0 = D_004802D0;
    t1 = D_00483538;
    D_0047FF58 = t0;
    D_0047FF5C = t1;
}
