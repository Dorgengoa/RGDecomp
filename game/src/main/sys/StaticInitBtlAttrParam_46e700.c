/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitBtlAttrParam_46e700 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004654F8;
extern s32 D_00465500;
extern s32 D_00466F38;
extern s32 D_00466F68;
extern s32 D_00480074;
extern s32 D_00480078;
extern s32 D_00483A60;
extern s32 D_00483A6C;
extern s32 D_00483A70;
extern s32 D_00483A7C;
extern s32 D_00483A80;
extern s32 D_00483A84;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitBtlAttrParam_46e700(void)
{
    IosBaseInitCtor_102bd0(&D_00483A6C);
    RegisterGlobalObject_100dc0(&D_00483A6C, IosBaseInitDtor_102ee0, &D_00483A60);
    WIosBaseInitCtor_103110(&D_00483A7C);
    RegisterGlobalObject_100dc0(&D_00483A7C, WIosBaseInitDtor_103420, &D_00483A70);
    D_00483A80 = D_00480074;
    *(s32 *)&D_00466F38 = D_004654F8;
    D_00483A84 = D_00480078;
    *(s32 *)&D_00466F68 = D_00465500;
}
