/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitMonsterParam_46f190 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00465530;
extern s32 D_00465538;
extern s32 D_00465540;
extern s32 D_00467CE8;
extern s32 D_00467D18;
extern s32 D_00467DD8;
extern s32 D_00480090;
extern s32 D_00480094;
extern s32 D_00480098;
extern s32 D_00483DF0;
extern s32 D_00483DFC;
extern s32 D_00483E00;
extern s32 D_00483E0C;
extern s32 D_00483E10;
extern s32 D_00483E14;
extern s32 D_00483E18;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitMonsterParam_46f190(void)
{
    IosBaseInitCtor_102bd0(&D_00483DFC);
    RegisterGlobalObject_100dc0(&D_00483DFC, IosBaseInitDtor_102ee0, &D_00483DF0);
    WIosBaseInitCtor_103110(&D_00483E0C);
    RegisterGlobalObject_100dc0(&D_00483E0C, WIosBaseInitDtor_103420, &D_00483E00);
    D_00483E10 = D_00480090;
    *(s32 *)&D_00467CE8 = D_00465530;
    D_00483E14 = D_00480094;
    *(s32 *)&D_00467D18 = D_00465538;
    D_00483E18 = D_00480098;
    *(s32 *)&D_00467DD8 = D_00465540;
}
