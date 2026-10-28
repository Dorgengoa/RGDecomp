/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitNpctParam_46f2b0 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00465568;
extern s32 D_00465570;
extern s32 D_00467EB8;
extern s32 D_00467EE8;
extern s32 D_004800B0;
extern s32 D_004800B4;
extern s32 D_00483E50;
extern s32 D_00483E5C;
extern s32 D_00483E60;
extern s32 D_00483E6C;
extern s32 D_00483E70;
extern s32 D_00483E74;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitNpctParam_46f2b0(void)
{
    IosBaseInitCtor_102bd0(&D_00483E5C);
    RegisterGlobalObject_100dc0(&D_00483E5C, IosBaseInitDtor_102ee0, &D_00483E50);
    WIosBaseInitCtor_103110(&D_00483E6C);
    RegisterGlobalObject_100dc0(&D_00483E6C, WIosBaseInitDtor_103420, &D_00483E60);
    D_00483E70 = D_004800B0;
    *(s32 *)&D_00467EB8 = D_00465568;
    D_00483E74 = D_004800B4;
    *(s32 *)&D_00467EE8 = D_00465570;
}
