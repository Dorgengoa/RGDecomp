/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitTranspParam_46f500 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00465590;
extern s32 D_00465598;
extern s32 D_004681E0;
extern s32 D_00468228;
extern s32 D_004800C4;
extern s32 D_004800C8;
extern s32 D_00483F18;
extern s32 D_00483F24;
extern s32 D_00483F28;
extern s32 D_00483F34;
extern s32 D_00483F3C;
extern s32 D_00483F40;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitTranspParam_46f500(void)
{
    IosBaseInitCtor_102bd0(&D_00483F24);
    RegisterGlobalObject_100dc0(&D_00483F24, IosBaseInitDtor_102ee0, &D_00483F18);
    WIosBaseInitCtor_103110(&D_00483F34);
    RegisterGlobalObject_100dc0(&D_00483F34, WIosBaseInitDtor_103420, &D_00483F28);
    D_00483F3C = D_004800C4;
    *(s32 *)&D_004681E0 = D_00465590;
    D_00483F40 = D_004800C8;
    *(s32 *)&D_00468228 = D_00465598;
}
