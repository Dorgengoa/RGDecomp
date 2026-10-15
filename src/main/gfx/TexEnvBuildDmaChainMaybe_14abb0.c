#include "types.h"

typedef unsigned __int128 u128;

extern u64 D_0047DEA0;
extern u64 D_0047DEB0;

struct Src {
    s32 m00;
    s16 m04;
    s8  m06;
    u8  pad007[5];
    u8 *m0C;
    u8  pad010[0x10];
    u128 m20;
};

s32 TexEnvBuildDmaChainMaybe_14abb0(struct Src *s, u128 *dst)
{
    u128 *p;

    if (s->m00 == 0 || s->m04 == 0) {
        return 0;
    }
        dst[0] = 0;
    ((u32 *)dst)[0] = s->m04 | 0x30000000;
    ((u32 *)dst)[1] = s->m00;
    p = dst + 1;
    if (s->m06 != 0) {
        p[0] = 0;
        ((u32 *)p)[0] = 0x10000001;
        ((u32 *)p)[2] = 0x01000101;
        ((u32 *)p)[3] = 0x6C010052;
        p[1] = s->m20;
        p += 2;
    }
    if (s->m0C != 0) {
        p[0] = *(u128 *)&D_0047DEA0;
        p[1] = *(u128 *)&D_0047DEB0;
        ((s64 *)p)[4] = *(s64 *)(s->m0C + 0x38);
        ((s64 *)p)[5] = 6;
        p += 3;
    }
    p[0] = 0;
    ((u32 *)p)[0] = 0x60000000;
    return (p + 1) - dst;
}
