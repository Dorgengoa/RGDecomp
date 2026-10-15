#include "types.h"

extern void ViBufReset_1d45b0(void *arg0);
extern void VoBufReset_1d4ab0(void *arg0);
extern void VideoDecDecodeBs_1d29e0(void *arg0);
extern void ThreadYield_1d2b70(void);
extern void VideoDecSetState_1d2b60(void *arg0, s32 arg1);
extern u8 D_004B3330[];
extern s32 D_004B3340[];

void VideoDecMain_1d5240(void *arg0) {
    ViBufReset_1d45b0((u8 *)arg0 + 0x48);
    VoBufReset_1d4ab0(D_004B3330);
    VideoDecDecodeBs_1d29e0(arg0);
    while (D_004B3340[0] != 0) {
        ThreadYield_1d2b70();
    }
    VideoDecSetState_1d2b60(arg0, 3);
}
