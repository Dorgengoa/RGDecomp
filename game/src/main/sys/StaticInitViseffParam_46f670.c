/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitViseffParam_46f670 1
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

extern s32 D_00465510;
extern s32 D_00468340;
extern s32 D_00480080;
extern s32 D_00483F98;
extern s32 D_00483FA4;
extern s32 D_00483FA8;
extern s32 D_00483FB4;
extern s32 D_00483FB8;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitViseffParam_46f670(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483FA4);
    RegisterGlobalObject_100dc0(&D_00483FA4, IosBaseInitDtor_102ee0, &D_00483F98);
    WIosBaseInitCtor_103110(&D_00483FB4);
    RegisterGlobalObject_100dc0(&D_00483FB4, WIosBaseInitDtor_103420, &D_00483FA8);
    t0 = D_00480080;
    t1 = D_00465510;
    D_00483FB8 = t0;
    *(s32 *)&D_00468340 = t1;
}
