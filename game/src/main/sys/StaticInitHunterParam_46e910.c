/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitHunterParam_46e910 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004655E8;
extern s32 D_004655F0;
extern s32 D_00467148;
extern s32 D_00467180;
extern s32 D_00480118;
extern s32 D_0048011C;
extern s32 D_00483B08;
extern s32 D_00483B14;
extern s32 D_00483B18;
extern s32 D_00483B24;
extern s32 D_00483B2C;
extern s32 D_00483B30;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitHunterParam_46e910(void)
{
    IosBaseInitCtor_102bd0(&D_00483B14);
    RegisterGlobalObject_100dc0(&D_00483B14, IosBaseInitDtor_102ee0, &D_00483B08);
    WIosBaseInitCtor_103110(&D_00483B24);
    RegisterGlobalObject_100dc0(&D_00483B24, WIosBaseInitDtor_103420, &D_00483B18);
    D_00483B2C = D_00480118;
    *(s32 *)&D_00467148 = D_004655E8;
    D_00483B30 = D_0048011C;
    *(s32 *)&D_00467180 = D_004655F0;
}
