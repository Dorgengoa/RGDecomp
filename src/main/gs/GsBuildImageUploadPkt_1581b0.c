#pragma optimization_level 3
#include "types.h"

#define LO32(v) ((s32)((v) & 0xFFFFFFFF))
#define HI32(v) ((s32)(((u64)(v) >> 32) & 0xFFFFFFFF))

s32 GsBuildImageUploadPkt_1581b0(s32 *p, s32 dbp, s32 dpsm, s32 dbw, s32 src, s32 qwc, s32 x, s32 y, s32 w, s32 h)
{
    s32 *start;
    u64 bbb;
    u64 pos;
    u64 reg;
    s32 n;

    start = p;
    p[0] = 0x10000006;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 5;
    p[5] = 0x10000000;
    p[6] = 0xE;
    p[7] = 0;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0x3F;
    p[11] = 0;
    bbb = ((s64)dpsm << 56) | (((s64)dbp << 32) | ((s64)dbw << 48));
    p[12] = LO32(bbb);
    p[13] = HI32(bbb);
    p[14] = 0x50;
    p[15] = 0;
    pos = (s64)x << 32;
    pos |= (s64)y << 48;
    p[16] = LO32(pos);
    p[17] = HI32(pos);
    p[18] = 0x51;
    p[19] = 0;
    reg = w | ((s64)h << 32);
    p[20] = LO32(reg);
    p[21] = HI32(reg);
    p[22] = 0x52;
    p[23] = 0;
    p[24] = 0;
    p[25] = 0;
    p[26] = 0x53;
    p[27] = 0;
    p += 28;
    while (qwc > 0) {
        n = 0x7FF0;
        if (qwc < 0x7FF0) n = qwc;
        p[0] = 0x10000001;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[4] = n | 0x8000;
        p[5] = 0x08000000;
        p[6] = 0;
        p[7] = 0;
        p[8] = n | 0x30000000;
        p[9] = src;
        p[10] = 0;
        p[11] = 0;
        src += n * 16;
        qwc -= 0x7FF0;
        p += 12;
    }
    return ((s32)p - (s32)start) / 4;
}
