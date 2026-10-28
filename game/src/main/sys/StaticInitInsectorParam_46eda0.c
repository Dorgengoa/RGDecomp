/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitInsectorParam_46eda0 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00465548;
extern s32 D_00465550;
extern s32 D_00467740;
extern s32 D_00467778;
extern s32 D_0048009C;
extern s32 D_004800A0;
extern s32 D_00483CB8;
extern s32 D_00483CC4;
extern s32 D_00483CC8;
extern s32 D_00483CD4;
extern s32 D_00483CD8;
extern s32 D_00483CDC;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitInsectorParam_46eda0(void)
{
    IosBaseInitCtor_102bd0(&D_00483CC4);
    RegisterGlobalObject_100dc0(&D_00483CC4, IosBaseInitDtor_102ee0, &D_00483CB8);
    WIosBaseInitCtor_103110(&D_00483CD4);
    RegisterGlobalObject_100dc0(&D_00483CD4, WIosBaseInitDtor_103420, &D_00483CC8);
    D_00483CD8 = D_0048009C;
    *(s32 *)&D_00467740 = D_00465548;
    D_00483CDC = D_004800A0;
    *(s32 *)&D_00467778 = D_00465550;
}
