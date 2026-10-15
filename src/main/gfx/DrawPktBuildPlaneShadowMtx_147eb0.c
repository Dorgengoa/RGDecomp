#include "types.h"
#pragma opt_propagation off

typedef unsigned __int128 u128;

extern void MtxPlaneProjection_13c930(u8 *arg0, u128 *arg1, u128 *arg2, u128 *arg3);

s32 DrawPktBuildPlaneShadowMtx_147eb0(u8 *arg0, u32 *arg1, u128 *arg2, s32 arg3)
{
    u32 *p;
    u32 *start;
    u32 *tag;
    u32 *cnt;
    s32 n;

    p = arg1;
    start = p;
    tag = p;
    cnt = p + 3;
    *(u128 *)p = 0;
    p[2] = 0x01000101;
    MtxPlaneProjection_13c930(arg0 + 0x3A30, arg2, arg2 + 1, arg2 + 2);
    ((u128 *)p)[1] = *(u128 *)(arg0 + 0x3A30);
    ((u128 *)p)[2] = *(u128 *)(arg0 + 0x3A40);
    ((u128 *)p)[3] = *(u128 *)(arg0 + 0x3A50);
    ((u128 *)p)[4] = *(u128 *)(arg0 + 0x3A60);
    ((u128 *)p)[5] = *arg2;
    p += 0x18;
    if (arg3 != 0) {
        p[0] = 0x8001;
        p[1] = 0x20000000;
        p[2] = 0x1E;
        p[3] = 0;
        *(s64 *)(p + 4) = 0x48;
        *(s64 *)(p + 6) = 0x42;
        p[8] = 1;
        p[9] = 1;
        p[10] = 1;
        p[11] = 0x80;
        p[12] = 0x8001;
        p[13] = 0x20000000;
        p[14] = 0x1E;
        p[15] = 0;
        *(s64 *)(p + 16) = 0x42;
        *(s64 *)(p + 18) = 0x42;
        p[20] = 1;
        p[21] = 1;
        p[22] = 1;
        p[23] = 0x80;
        p += 0x18;
    }
    n = (s32)((u8 *)p - (u8 *)start) / 4 / 4;
    *cnt = ((n - 1) << 16) | 0x6C00001E;
    *tag = (n - 1) | 0x60000000;
    return n;
}
