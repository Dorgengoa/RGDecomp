/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitBtlJdgObjParam_46e8a0 1
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

extern s32 D_00465508;
extern s32 D_00467100;
extern s32 D_0048007C;
extern s32 D_00483AE0;
extern s32 D_00483AEC;
extern s32 D_00483AF0;
extern s32 D_00483AFC;
extern s32 D_00483B00;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitBtlJdgObjParam_46e8a0(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483AEC);
    RegisterGlobalObject_100dc0(&D_00483AEC, IosBaseInitDtor_102ee0, &D_00483AE0);
    WIosBaseInitCtor_103110(&D_00483AFC);
    RegisterGlobalObject_100dc0(&D_00483AFC, WIosBaseInitDtor_103420, &D_00483AF0);
    t0 = D_0048007C;
    t1 = D_00465508;
    D_00483B00 = t0;
    *(s32 *)&D_00467100 = t1;
}
