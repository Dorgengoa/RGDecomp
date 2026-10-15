#include "types.h"

#pragma divbyzerocheck on
typedef struct {
    u8 pad0[0x44];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
} T1d2df0_arg4;

void AudioDecIopGetArea_1d2df0(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, T1d2df0_arg4 *arg4, s32 arg5) {
    s32 temp_11;
    s32 temp_10;
    s32 temp_9;

    temp_11 = arg4->unk48;
    temp_10 = arg4->unk4C;
    temp_9 = (((arg5 + temp_11) - temp_10 - 0x400) % temp_11) / 1024 * 1024;
    if ((temp_11 - temp_10) >= temp_9) {
        *arg0 = arg4->unk44 + temp_10;
        *arg1 = temp_9;
        *arg3 = 0;
        *arg2 = 0;
    } else {
        *arg0 = arg4->unk44 + temp_10;
        *arg1 = arg4->unk48 - arg4->unk4C;
        *arg2 = arg4->unk44;
        *arg3 = temp_9 - (arg4->unk48 - arg4->unk4C);
    }
}
