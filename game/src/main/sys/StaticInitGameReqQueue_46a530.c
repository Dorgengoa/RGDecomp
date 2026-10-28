/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitGameReqQueue_46a530 1
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

extern s32 D_00481978;
extern s32 D_00481984;
extern s32 D_00481988;
extern s32 D_00481994;
extern s32 D_004819A0;
extern u8 D_004B5160[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitGameReqQueue_46a530(void)
{
    IosBaseInitCtor_102bd0(&D_00481984);
    RegisterGlobalObject_100dc0(&D_00481984, IosBaseInitDtor_102ee0, &D_00481978);
    WIosBaseInitCtor_103110(&D_00481994);
    RegisterGlobalObject_100dc0(&D_00481994, WIosBaseInitDtor_103420, &D_00481988);
    GameReqListInit_20a560(&D_004819A0);
    LoaderClear_1ce040(D_004B5160);
}
