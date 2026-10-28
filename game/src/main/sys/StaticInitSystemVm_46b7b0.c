/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitSystemVm_46b7b0 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F58;
extern s32 D_00481F64;
extern s32 D_00481F68;
extern s32 D_00481F74;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];
extern u8 gSystemVm[];

void StaticInitSystemVm_46b7b0(void)
{
    IosBaseInitCtor_102bd0(&D_00481F64);
    RegisterGlobalObject_100dc0(&D_00481F64, IosBaseInitDtor_102ee0, &D_00481F58);
    WIosBaseInitCtor_103110(&D_00481F74);
    RegisterGlobalObject_100dc0(&D_00481F74, WIosBaseInitDtor_103420, &D_00481F68);
    ScriptVmCtor_176be0(gSystemVm);
}
