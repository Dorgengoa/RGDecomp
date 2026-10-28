/* rgp:protos */
#define RGP_SELF_StaticInitWorldDataEntries_46e080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004836E8;
extern u8 D_004836F4;
extern u8 D_004836F8;
extern u8 D_00483704;
extern f32 D_0045B078;
extern s32 D_004644B8;
extern s32 D_004644D8;

#pragma opt_propagation off
void StaticInitWorldDataEntries_46e080(void)
{
    f32 d;
    s32 v;

    IosBaseInitCtor_102bd0(&D_004836F4);
    RegisterGlobalObject_100dc0(&D_004836F4, (void *)IosBaseInitDtor_102ee0, &D_004836E8);
    WIosBaseInitCtor_103110(&D_00483704);
    RegisterGlobalObject_100dc0(&D_00483704, (void *)WIosBaseInitDtor_103420, &D_004836F8);
    d = D_0045B078;
    v = (s32)(3.0f * d);
    *(s32 *)&D_004644B8 = v;
    *(s32 *)&D_004644D8 = v;
}
