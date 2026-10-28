/* rgp:protos */
#define RGP_SELF_StaticInitParamScript_469550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A branch-free STATIC INITIALISER (the IosBaseInitCtor_102bd0 / RegisterGlobalObject_100dc0 family).
   Drafted by build/rk_ctor.py: m2c gives the order and the arguments, the
   listing gives each global's RELOCATION -- %gp_rel means a plain extern,
   %hi/%lo means an incomplete array, because a written global cannot take
   the `const` escape out of small data. */

extern s32 memset(void *, s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004813C8;
extern s32 D_004813D4;
extern s32 D_004813D8;
extern s32 D_004813E4;
extern u8 D_0049D450[];
extern void * D_0049D47C[];
extern s32 D_0049D480[];
extern void * D_0049D488[];
extern s32 D_0049D48C[];
extern u8 D_0049D490[];
extern u8 D_0049D4B0[];
extern s32 D_0049D4F8[];
extern s32 D_0049D4FC[];

void StaticInitParamScript_469550(void)
{
    IosBaseInitCtor_102bd0(&D_004813D4);
    RegisterGlobalObject_100dc0(&D_004813D4, IosBaseInitDtor_102ee0, &D_004813C8);
    WIosBaseInitCtor_103110(&D_004813E4);
    RegisterGlobalObject_100dc0(&D_004813E4, WIosBaseInitDtor_103420, &D_004813D8);
    memset(D_0049D450, 0, 0x88);
    D_0049D480[0] = 8;
    D_0049D47C[0] = D_0049D490;
    D_0049D48C[0] = 8;
    D_0049D488[0] = D_0049D4B0;
    D_0049D4F8[0] = 0;
    D_0049D4FC[0] = 0;
}
