/* rgp:protos */
#define RGP_SELF_InvIdGetMinorIndex_3d5440 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern s32 D_00465A78[4],D_00465AE8[4],D_00465B00[4];
#include "types.h"
#pragma divbyzerocheck on

/*rgp*/
extern s32 D_004659F0[4];
extern s32 D_00465A00[4];
extern s32 D_00465A08[4];
extern s32 D_00465A20[4];
extern s32 D_00465A30[4];
extern s32 D_00465A38[4];
extern s32 D_00465A48[4];
extern s32 D_00465A60[4];
extern s32 D_00465AB8[4];
extern s32 D_00465AD0[4];
extern s32 D_00465B18[4];
extern s32 D_00465B28[4];
extern s32 D_00465B30[4];

s32 InvIdGetMinorIndex_3d5440(s32 arg0)
{
    switch (InvGetCategoryOfId_3d56f0((int)arg0)) {
    case 0:
        return (arg0 - D_00465A08[0]) % D_00465A00[0] % D_004659F0[0];
    case 1:
        return (arg0 - D_00465A38[0]) % D_00465A30[0] % D_00465A20[0];
    case 2:
        return (arg0 - D_00465A60[0]) % D_00465A48[0];
    case 3:
        return arg0-D_00465A78[0];
    case 6:
        return (arg0 - D_00465AD0[0]) % D_00465AB8[0];
    case 7:
        return arg0-D_00465AE8[0];
    case 8:
        return arg0-D_00465B00[0];
    case 9:
        return (arg0 - D_00465B30[0]) % D_00465B28[0] % D_00465B18[0];
    default:
        return -1;
    }
}
