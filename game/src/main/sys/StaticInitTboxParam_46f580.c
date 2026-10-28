/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitTboxParam_46f580 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004655A0;
extern s32 D_004655A8;
extern s32 D_00468258;
extern s32 D_00468298;
extern s32 D_004800CC;
extern s32 D_004800D0;
extern s32 D_00483F48;
extern s32 D_00483F54;
extern s32 D_00483F58;
extern s32 D_00483F64;
extern s32 D_00483F68;
extern s32 D_00483F6C;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitTboxParam_46f580(void)
{
    IosBaseInitCtor_102bd0(&D_00483F54);
    RegisterGlobalObject_100dc0(&D_00483F54, IosBaseInitDtor_102ee0, &D_00483F48);
    WIosBaseInitCtor_103110(&D_00483F64);
    RegisterGlobalObject_100dc0(&D_00483F64, WIosBaseInitDtor_103420, &D_00483F58);
    D_00483F68 = D_004800CC;
    *(s32 *)&D_00468258 = D_004655A0;
    D_00483F6C = D_004800D0;
    *(s32 *)&D_00468298 = D_004655A8;
}
