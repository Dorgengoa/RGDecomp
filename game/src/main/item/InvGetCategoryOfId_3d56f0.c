/* rgp:protos */
#define RGP_SELF_InvGetCategoryOfId_3d56f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00465A08[8];
extern u8 D_00465A10[8];
extern u8 D_00465A38[8];
extern u8 D_00465A40[8];
extern u8 D_00465A60[8];
extern u8 D_00465A68[8];
extern u8 D_00465A78[8];
extern u8 D_00465A80[8];
extern u8 D_00465A90[8];
extern u8 D_00465A98[8];
extern u8 D_00465AA8[8];
extern u8 D_00465AB0[8];
extern u8 D_00465AD0[8];
extern u8 D_00465AD8[8];
extern u8 D_00465AE8[8];
extern u8 D_00465AF0[8];
extern u8 D_00465B00[8];
extern u8 D_00465B08[8];
extern u8 D_00465B30[8];
extern u8 D_00465B38[0x400];

s32 InvGetCategoryOfId_3d56f0(s32 arg0) {
    if (arg0 < 0) {
        return -1;
    }
    if (arg0 >= *(s32 *)D_00465A08 && arg0 <= *(s32 *)D_00465A10) {
        return 0;
    }
    if (arg0 >= *(s32 *)D_00465A38 && arg0 <= *(s32 *)D_00465A40) {
        return 1;
    }
    if (arg0 >= *(s32 *)D_00465A60 && arg0 <= *(s32 *)D_00465A68) {
        return 2;
    }
    if (arg0 >= *(s32 *)D_00465A78 && arg0 <= *(s32 *)D_00465A80) {
        return 3;
    }
    if (arg0 >= *(s32 *)D_00465A90 && arg0 <= *(s32 *)D_00465A98) {
        return 4;
    }
    if (arg0 >= *(s32 *)D_00465AA8 && arg0 <= *(s32 *)D_00465AB0) {
        return 5;
    }
    if (arg0 >= *(s32 *)D_00465AD0 && arg0 <= *(s32 *)D_00465AD8) {
        return 6;
    }
    if (arg0 >= *(s32 *)D_00465AE8 && arg0 <= *(s32 *)D_00465AF0) {
        return 7;
    }
    if (arg0 >= *(s32 *)D_00465B00 && arg0 <= *(s32 *)D_00465B08) {
        return 8;
    }
    if (arg0 >= *(s32 *)D_00465B30 && arg0 <= *(s32 *)D_00465B38) {
        return 9;
    }
    return -1;
}
