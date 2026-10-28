/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitCharaParam_46ea80 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00465518;
extern s32 D_00465520;
extern s32 D_00465528;
extern s32 D_004672E0;
extern s32 D_00467330;
extern s32 D_00467388;
extern s32 D_00480084;
extern s32 D_00480088;
extern s32 D_0048008C;
extern s32 D_00483B88;
extern s32 D_00483B94;
extern s32 D_00483B98;
extern s32 D_00483BA4;
extern s32 D_00483BC0;
extern s32 D_00483BC4;
extern s32 D_00483BC8;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitCharaParam_46ea80(void)
{
    IosBaseInitCtor_102bd0(&D_00483B94);
    RegisterGlobalObject_100dc0(&D_00483B94, IosBaseInitDtor_102ee0, &D_00483B88);
    WIosBaseInitCtor_103110(&D_00483BA4);
    RegisterGlobalObject_100dc0(&D_00483BA4, WIosBaseInitDtor_103420, &D_00483B98);
    D_00483BC0 = D_00480084;
    *(s32 *)&D_004672E0 = D_00465518;
    D_00483BC4 = D_00480088;
    *(s32 *)&D_00467330 = D_00465520;
    D_00483BC8 = D_0048008C;
    *(s32 *)&D_00467388 = D_00465528;
}
