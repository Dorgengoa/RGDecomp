/* rgp:protos */
#define RGP_SELF_StaticInitInsectCageMenu_46dce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A branch-free STATIC INITIALISER (the IosBaseInitCtor_102bd0 / RegisterGlobalObject_100dc0 family).
   Drafted by build/rk_ctor.py: m2c gives the order and the arguments, the
   listing gives each global's RELOCATION -- %gp_rel means a plain extern,
   %hi/%lo means an incomplete array, because a written global cannot take
   the `const` escape out of small data. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00483278;
extern s32 D_00483284;
extern s32 D_00483288;
extern s32 D_00483294;
extern s32 D_004832B8;
extern s32 D_004832BC;
extern s32 D_0048335C;
extern s32 D_00483360;
extern u8 D_004E9280[];
extern u8 D_004E9320[];
extern u8 D_004E9380[];
extern u8 D_004E93E0[];
extern u8 D_004E9440[];
extern u8 D_004E9510[];

void StaticInitInsectCageMenu_46dce0(void)
{
    IosBaseInitCtor_102bd0(&D_00483284);
    RegisterGlobalObject_100dc0(&D_00483284, IosBaseInitDtor_102ee0, &D_00483278);
    WIosBaseInitCtor_103110(&D_00483294);
    RegisterGlobalObject_100dc0(&D_00483294, WIosBaseInitDtor_103420, &D_00483288);
    MenuObjParamsCtor_388010(D_004E9280);
    MemStackCtor_14e030(D_004E9320);
    MemStackCtor_14e030(D_004E9380);
    MemStackCtor_14e030(D_004E93E0);
    MemStackCtor_14e030(D_004E9440);
    D_004832B8 = 0;
    D_004832BC = 0;
    ConstructArray_100620(D_004E9510, InsectCageItemIconCtor_386090, 0, 0x20, 2);
    BitArray16Ctor_3842e0(&D_0048335C);
    BitArray16Ctor_3842e0(&D_00483360);
}
