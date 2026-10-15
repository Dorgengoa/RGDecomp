#include "types.h"

extern void DeleteThread(s32 arg0);
extern void DisableDmac_117150(s32 arg0);
extern void CdDiskWatchSetEnabled_17fe80(s32 arg0);
extern void ThreadYield_1d2b70(void);
extern void AudioDecReset_1d3070(void *arg0);
extern void AudioDecDelete_1d31d0(void *arg0);
extern void MovieStreamClose_1d3660(void *arg0);
extern void VideoDecFlush_1d5310(void *arg0, void *arg1);
extern void VideoDecDelete_1d53f0(void *arg0, void *arg1);
extern void RemoveDmacHandler(s32 arg0, s32 arg1);
extern void RemoveIntcHandler(s32 arg0, s32 arg1);
extern void TerminateThread(s32 arg0);
extern s32 D_004817E0;
extern s32 D_004817E4;
extern u8 D_004B3210[];
extern s32 D_004B32C0[];
extern s32 D_004B32C4[];
extern u8 D_004B32D0[];
extern u8 D_004B3350[];

typedef struct S1D5 {
    u8 pad0[0x17900];
    u8 unk17900;
    u8 pad17901[3];
    s32 unk17904;
    s32 unk17908;
    s32 unk1790C;
    s32 unk17910;
} S1D5;

void MoviePlayerShutdown_1d56c0(S1D5 *arg0)
{
    if (arg0->unk17900 != 0) {
        VideoDecFlush_1d5310(arg0, D_004B3210);
        ThreadYield_1d2b70();
        D_004817E4 = 1;
        while (((D_004817E0 != 0) ^ 1) != 0) {
            ThreadYield_1d2b70();
        }
        TerminateThread(arg0->unk1790C);
        TerminateThread(arg0->unk17904);
        TerminateThread(arg0->unk17908);
        DeleteThread(arg0->unk1790C);
        DeleteThread(arg0->unk17904);
        DeleteThread(arg0->unk17908);
        DisableDmac_117150(2);
        RemoveDmacHandler(2, D_004B32C0[0]);
        RemoveIntcHandler(2, D_004B32C4[0]);
        arg0->unk17900 = 0;
    }
    VideoDecDelete_1d53f0(arg0, D_004B3210);
    AudioDecReset_1d3070(D_004B32D0);
    AudioDecDelete_1d31d0(D_004B32D0);
    MovieStreamClose_1d3660(D_004B3350);
    CdDiskWatchSetEnabled_17fe80(arg0->unk17910);
}
