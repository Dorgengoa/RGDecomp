/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitBtlElemParam_46e780 1
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

extern s32 D_004654F0;
extern s32 D_00466FB8;
extern s32 D_00480070;
extern s32 D_00483A88;
extern s32 D_00483A94;
extern s32 D_00483A98;
extern s32 D_00483AA4;
extern s32 D_00483AA8;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitBtlElemParam_46e780(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483A94);
    RegisterGlobalObject_100dc0(&D_00483A94, IosBaseInitDtor_102ee0, &D_00483A88);
    WIosBaseInitCtor_103110(&D_00483AA4);
    RegisterGlobalObject_100dc0(&D_00483AA4, WIosBaseInitDtor_103420, &D_00483A98);
    t0 = D_00480070;
    t1 = D_004654F0;
    D_00483AA8 = t0;
    *(s32 *)&D_00466FB8 = t1;
}
