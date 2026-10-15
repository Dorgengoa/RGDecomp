#include "types.h"

extern f32 CharaGetHeightAboveGround_238380(void);
extern u8 D_0045B080[0x400];
extern f32 D_0047DADC;

s32 CharaHasLandedMaybe_20fdb0(void *arg0) {
    s32 temp_3;
    s32 var_2;

    if (*(s64 *)((u8 *)arg0 + 0x3D0) & ((s64)0x4000 << 0x20)) {
        return 1;
    }
    temp_3 = *(s32 *)((u8 *)arg0 + 0x3D8);
    if (!(!(temp_3 & 1))) {
        return 1;
    }
    if (!(temp_3 & 4)) {
        return 1;
    }
    if (!(CharaGetHeightAboveGround_238380() < ((D_0047DADC * (*(volatile f32 *)D_0045B080)) - *(f32 *)((u8 *)arg0 + 0x84)))) {
        var_2 = 0;
    } else {
        var_2 = 1;
    }
    return var_2;
    return 1;
}
