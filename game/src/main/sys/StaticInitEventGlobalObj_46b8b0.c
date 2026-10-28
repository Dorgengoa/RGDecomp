/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitEventGlobalObj_46b8b0 1
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

extern s32 D_00481FC0;
extern s32 D_00481FCC;
extern s32 D_00481FD0;
extern s32 D_00481FDC;
extern u8 D_004BD2D0[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitEventGlobalObj_46b8b0(void)
{
    IosBaseInitCtor_102bd0(&D_00481FCC);
    RegisterGlobalObject_100dc0(&D_00481FCC, IosBaseInitDtor_102ee0, &D_00481FC0);
    WIosBaseInitCtor_103110(&D_00481FDC);
    RegisterGlobalObject_100dc0(&D_00481FDC, WIosBaseInitDtor_103420, &D_00481FD0);
    EventGlobalObjCtor_257a10(D_004BD2D0);
}
