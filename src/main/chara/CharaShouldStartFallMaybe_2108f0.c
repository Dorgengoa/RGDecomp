#include "types.h"

extern f32 CharaGetHeightAboveGround_238380(void *);
extern const f32 D_0045B080;

s32 CharaShouldStartFallMaybe_2108f0(void *arg0) {
    s64 temp_5;
    s32 temp_3;

    temp_5 = *(s64 *)((u8 *)arg0 + 0x3D0);
    if (temp_5 & (0x80000LL << 0x20)) {
        return 0;
    }
    temp_3 = *(s32 *)((u8 *)arg0 + 0xA44);
    if (temp_3 & 0x20000) {
        return 0;
    }
    if (temp_3 & 0x10000) {
        return 0;
    }
    if (temp_5 & (0x4000LL << 0x20)) {
        return 0;
    }
    temp_3 = *(s32 *)((u8 *)arg0 + 0x3D8);
    if (temp_3 & 1) {
        return 0;
    }
    if (!(temp_3 & 4)) {
        return 0;
    }
    if (CharaGetHeightAboveGround_238380(arg0) > (1.25f * D_0045B080)) {
        return 1;
    }
    return 0;
}
