/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitNpcParam_46f230 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00465558;
extern s32 D_00465560;
extern s32 D_00467E10;
extern s32 D_00467E48;
extern s32 D_004800A4;
extern s32 D_004800AC;
extern s32 D_00483E20;
extern s32 D_00483E2C;
extern s32 D_00483E30;
extern s32 D_00483E3C;
extern s32 D_00483E40;
extern s32 D_00483E48;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitNpcParam_46f230(void)
{
    IosBaseInitCtor_102bd0(&D_00483E2C);
    RegisterGlobalObject_100dc0(&D_00483E2C, IosBaseInitDtor_102ee0, &D_00483E20);
    WIosBaseInitCtor_103110(&D_00483E3C);
    RegisterGlobalObject_100dc0(&D_00483E3C, WIosBaseInitDtor_103420, &D_00483E30);
    D_00483E40 = D_004800A4;
    *(s32 *)&D_00467E10 = D_00465558;
    D_00483E48 = D_004800AC;
    *(s32 *)&D_00467E48 = D_00465560;
}
