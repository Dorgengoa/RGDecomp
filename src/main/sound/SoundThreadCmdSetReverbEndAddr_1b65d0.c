#include "types.h"

extern void sceSdRemote_1229e8(s32, s32, s32, s32);

s32 SoundThreadCmdSetReverbEndAddr_1b65d0(void *arg0) {
    s32 temp16;
    s32 temp17;

    temp16 = *(s32 *)((u8 *)arg0 + 0x0) != 0;
    temp17 = *(s32 *)((u8 *)arg0 + 0x8);
    sceSdRemote_1229e8(1, 0x8070, temp16 | 2, 0);
    sceSdRemote_1229e8(1, 0x8050, temp16 | 0x1D00, temp17);
    return 0;
}
