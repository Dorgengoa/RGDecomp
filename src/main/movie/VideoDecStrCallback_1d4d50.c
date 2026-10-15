#include "types.h"
#pragma opt_propagation off

extern s32 Copy2Area_1d2610(u64 arg0, s32 arg1, u64 arg2, s32 arg3, s32 arg4, u32 arg5, void *arg6, s32 arg7);
extern void VideoDecEndPut_1d2740(void *arg0, s32 arg1);
extern void VideoDecPutTs_1d2750(void *arg0, s64 arg1, s64 arg2, s32 arg3, s32 arg4);
extern void VideoDecBeginPut_1d2790(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4);
extern u8 D_004B3210[0x40];

s32 VideoDecStrCallback_1d4d50(s32 unused0, void *arg1, void *arg2)
{
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 a;
    u32 n;
    s32 r;
    s32 k;
    u32 m;

    a = *(s32 *)((u8 *)arg1 + 0x8);
    n = *(u32 *)((u8 *)arg1 + 0xC);
    m = ((u32)((u8 *)arg2 + *(s32 *)((u8 *)arg2 + 0x14008))) - a;
    if (n < m) {
        m = n;
    }
    k = n - m;
    VideoDecBeginPut_1d2790(D_004B3210, &sp6C, &sp64, &sp68, &sp60);
    r = Copy2Area_1d2610(((u64)((s64)sp6C << 0x24) >> 0x24) | 0x20000000, sp64,
                     ((u64)((s64)sp68 << 0x24) >> 0x24) | 0x20000000, sp60,
                     a, m, arg2, k);
    if (r > 0) {
        VideoDecPutTs_1d2750(D_004B3210, *(s64 *)((u8 *)arg1 + 0x10), *(s64 *)((u8 *)arg1 + 0x18), sp6C, r);
    }
    VideoDecEndPut_1d2740(D_004B3210, r);
    return r > 0;
}
