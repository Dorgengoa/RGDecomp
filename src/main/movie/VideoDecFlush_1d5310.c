#include "types.h"

extern s32 Copy2Area_1d2610(u64 arg0, s32 arg1, u64 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7);
extern void VideoDecEndPut_1d2740(void *arg0, s32 arg1);
extern void VideoDecBeginPut_1d2790(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4);
extern void ViBufFlush_1d3dd0(void *arg0);
extern u8 D_0047E300;
extern u8 D_0047E301;
extern u8 D_0047E302;
extern u8 D_0047E303;
extern u8 D_004B3210[0x40];

s32 VideoDecFlush_1d5310(s32 unused0, u8 *arg1)
{
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 n1;
    s32 n2;
    u8 buf[4];
    u64 a;
    u64 c;
    VideoDecBeginPut_1d2790(arg1, &sp3C, &sp34, &sp38, &sp30);
    n2 = sp30;
    n1 = sp34;
    if (n1 + n2 < 4) {
        return 0;
    }
    a = sp3C;
    c = sp38;
    a = (a & 0x0FFFFFFF) | 0x20000000;
    c = (c & 0x0FFFFFFF) | 0x20000000;
    buf[0] = D_0047E300;
    buf[1] = D_0047E301;
    *(u8 *)((u32)buf + 2) = D_0047E302;
    buf[3] = D_0047E303;
    VideoDecEndPut_1d2740(D_004B3210, Copy2Area_1d2610(a, n1, c, n2, buf, 4, 0, 0));
    ViBufFlush_1d3dd0(arg1 + 0x48);
    if (*(s32 *)(arg1 + 0xA8) == 0) {
        *(s32 *)(arg1 + 0xA8) = 2;
    }
    return 1;
}
