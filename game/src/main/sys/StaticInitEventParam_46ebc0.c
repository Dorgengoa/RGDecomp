/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitEventParam_46ebc0 1
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

extern s32 D_004654A0;
extern s32 D_00467528;
extern s32 D_00480048;
extern s32 D_00483C00;
extern s32 D_00483C0C;
extern s32 D_00483C10;
extern s32 D_00483C1C;
extern s32 D_00483C20;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitEventParam_46ebc0(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483C0C);
    RegisterGlobalObject_100dc0(&D_00483C0C, IosBaseInitDtor_102ee0, &D_00483C00);
    WIosBaseInitCtor_103110(&D_00483C1C);
    RegisterGlobalObject_100dc0(&D_00483C1C, WIosBaseInitDtor_103420, &D_00483C10);
    t0 = D_00480048;
    t1 = D_004654A0;
    D_00483C20 = t0;
    *(s32 *)&D_00467528 = t1;
}
