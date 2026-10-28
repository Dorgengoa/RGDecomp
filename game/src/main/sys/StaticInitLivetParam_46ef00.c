/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitLivetParam_46ef00 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004655C0;
extern s32 D_004655C8;
extern s32 D_00467928;
extern s32 D_00467970;
extern s32 D_004800DC;
extern s32 D_004800E0;
extern s32 D_00483D48;
extern s32 D_00483D54;
extern s32 D_00483D58;
extern s32 D_00483D64;
extern s32 D_00483D68;
extern s32 D_00483D6C;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitLivetParam_46ef00(void)
{
    IosBaseInitCtor_102bd0(&D_00483D54);
    RegisterGlobalObject_100dc0(&D_00483D54, IosBaseInitDtor_102ee0, &D_00483D48);
    WIosBaseInitCtor_103110(&D_00483D64);
    RegisterGlobalObject_100dc0(&D_00483D64, WIosBaseInitDtor_103420, &D_00483D58);
    D_00483D68 = D_004800DC;
    *(s32 *)&D_00467928 = D_004655C0;
    D_00483D6C = D_004800E0;
    *(s32 *)&D_00467970 = D_004655C8;
}
