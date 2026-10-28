/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitCaption_46d200 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482C90;
extern s32 D_00482C9C;
extern s32 D_00482CA0;
extern s32 D_00482CAC;
extern u8 D_004E8850[];
extern u8 D_004E88B0[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitCaption_46d200(void)
{
    IosBaseInitCtor_102bd0(&D_00482C9C);
    RegisterGlobalObject_100dc0(&D_00482C9C, IosBaseInitDtor_102ee0, &D_00482C90);
    WIosBaseInitCtor_103110(&D_00482CAC);
    RegisterGlobalObject_100dc0(&D_00482CAC, WIosBaseInitDtor_103420, &D_00482CA0);
    CaptionCfgCtor_3402e0(D_004E8850);
    CaptionPanelCtor_33eb70(D_004E88B0);
}
