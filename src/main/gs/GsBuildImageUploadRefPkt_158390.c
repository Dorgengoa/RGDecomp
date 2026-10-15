#pragma optimization_level 3
#pragma opt_propagation off
#pragma opt_pulloutconstants off
#include "types.h"

#define LO(x) ((u32)((x) & 0xFFFFFFFF))
#define HI(x) ((u32)(((x) >> 32) & 0xFFFFFFFF))

s32 GsBuildImageUploadRefPkt_158390(u32 *p, s32 dbp, s32 dpsm, s32 dbw, s32 addr, s32 qwc, s32 dsax, s32 dsay, s32 rrw, s32 rrh) {
    u32 *start;
    u64 bitblt;
    u64 trxpos;
    u64 trxreg;
    s32 off;
    s32 n;
    u32 c1;

    start = p;
    p[0] = 0x10000006;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x50000006;
    p[4] = 5;
    p[5] = 0x10000000;
    p[6] = 0xE;
    p[7] = 0;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0x3F;
    bitblt = ((u64)dbp << 32) | ((u64)dbw << 48) | ((u64)dpsm << 56);
    p[11] = 0;
    p[12] = LO(bitblt);
    p[13] = HI(bitblt);
    p[14] = 0x50;
    trxpos = ((u64)dsax << 32) | ((u64)dsay << 48);
    p[15] = 0;
    trxreg = (u64)rrw | ((u64)rrh << 32);
    p[16] = LO(trxpos);
    p[17] = HI(trxpos);
    p[18] = 0x51;
    p[19] = 0;
    p[20] = LO(trxreg);
    p[21] = HI(trxreg);
    p[22] = 0x52;
    p[23] = 0;
    p[24] = 0;
    p[25] = 0;
    p[26] = 0x53;
    off = addr & 0x7F;
    p[27] = 0;
    p += 0x1C;
    if (off != 0x10) {
        p[0] = 0x10000001;
        p[1] = 0;
        p[2] = 0;
        n = 0x90 - off;
        p[3] = 0x50000001;
        n = n / 16;
        p[4] = n | 0x8000;
        p[5] = 0x08000000;
        p[6] = 0;
        p[7] = 0;
        p[8] = n | 0x30000000;
        p[9] = addr;
        p[10] = 0;
        p[11] = n | 0x50000000;
        qwc -= n;
        addr += n * 16;
        p += 0xC;
    }
    c1 = 0x10000001;
    for (; qwc > 0; qwc -= 0x7FF0) {
        n = 0x7FF0;
        if (qwc < 0x7FF0) {
            n = qwc;
        }
        p[0] = c1;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0x50000001;
        p[4] = n | 0x8000;
        p[5] = 0x08000000;
        p[6] = 0;
        p[7] = 0;
        p[8] = n | 0x30000000;
        p[9] = addr;
        p[10] = 0;
        p[11] = n | 0x50000000;
        addr += n * 16;
        p += 0xC;
    }
    return p - start;
}
