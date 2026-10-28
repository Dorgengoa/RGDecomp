/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitInsectronParam_46ee20 1
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

extern s32 D_00465630;
extern s32 D_004677B0;
extern s32 D_00480114;
extern s32 D_00483CE0;
extern s32 D_00483CEC;
extern s32 D_00483CF0;
extern s32 D_00483CFC;
extern s32 D_00483D00;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitInsectronParam_46ee20(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483CEC);
    RegisterGlobalObject_100dc0(&D_00483CEC, IosBaseInitDtor_102ee0, &D_00483CE0);
    WIosBaseInitCtor_103110(&D_00483CFC);
    RegisterGlobalObject_100dc0(&D_00483CFC, WIosBaseInitDtor_103420, &D_00483CF0);
    t0 = D_00480114;
    t1 = D_00465630;
    D_00483D00 = t0;
    *(s32 *)&D_004677B0 = t1;
}
