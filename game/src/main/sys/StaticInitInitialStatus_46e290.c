/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitInitialStatus_46e290 1
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

extern s32 D_00465650;
extern s32 D_00466028;
extern s32 D_00480164;
extern s32 D_00483828;
extern s32 D_00483834;
extern s32 D_00483838;
extern s32 D_00483844;
extern s32 D_00483848;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitInitialStatus_46e290(void)
{
    s32 t0;
    s32 t1;

    IosBaseInitCtor_102bd0(&D_00483834);
    RegisterGlobalObject_100dc0(&D_00483834, IosBaseInitDtor_102ee0, &D_00483828);
    WIosBaseInitCtor_103110(&D_00483844);
    RegisterGlobalObject_100dc0(&D_00483844, WIosBaseInitDtor_103420, &D_00483838);
    t0 = D_00480164;
    t1 = D_00465650;
    D_00483848 = t0;
    *(s32 *)&D_00466028 = t1;
}
