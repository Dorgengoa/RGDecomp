/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitAbilityParam_46e5d0 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004654B8;
extern s32 D_004654C0;
extern s32 D_00466D90;
extern s32 D_00466E28;
extern s32 D_00480054;
extern s32 D_00480058;
extern s32 D_00483A08;
extern s32 D_00483A14;
extern s32 D_00483A18;
extern s32 D_00483A24;
extern s32 D_00483A28;
extern s32 D_00483A2C;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitAbilityParam_46e5d0(void)
{
    IosBaseInitCtor_102bd0(&D_00483A14);
    RegisterGlobalObject_100dc0(&D_00483A14, IosBaseInitDtor_102ee0, &D_00483A08);
    WIosBaseInitCtor_103110(&D_00483A24);
    RegisterGlobalObject_100dc0(&D_00483A24, WIosBaseInitDtor_103420, &D_00483A18);
    D_00483A28 = D_00480054;
    *(s32 *)&D_00466D90 = D_004654B8;
    D_00483A2C = D_00480058;
    *(s32 *)&D_00466E28 = D_004654C0;
}
