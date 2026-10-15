#pragma opt_loop_invariants off
#include "types.h"

extern s32 D_0044AEB0[];

s32 SoundAdpcmDecodeBlock_1bc030(u8 *arg0, s32 arg1, s16 *out, u8 *in)
{
    s32 *tbl;
    s16 hv;
    u16 hdr;
    u32 idx;
    s32 pos;
    s32 neg;
    u8 *p;
    s32 n;
    u8 *st;
    s32 *p7C;
    s32 *p80;
    s32 *p84;
    s32 h1;
    s32 h2;
    s32 h3;
    u8 *row;
    s32 c10;
    s32 c14;
    s32 c18;
    u32 b;
    s32 hi;
    s32 lo;
    s32 acc;
    s32 x;
    s32 y;

    tbl = D_0044AEB0;
    hv = (s32)in[0];
    hv |= (s16)(in[1] << 8);
    hdr = hv;
    idx = (hdr >> 10) & 0x1F;
    pos = tbl[(hdr >> 5) & 0x1F];
    neg = tbl[hdr & 0x1F];
    p = in + 2;
    if (idx >= *(u32 *)(*(s32 *)(arg0 + 0x78) + 0xC)) {
        idx = 0;
    }
    p7C = (s32 *)(arg0 + 0x7C) + arg1 * 3;
    p80 = (s32 *)(arg0 + 0x80) + arg1 * 3;
    p84 = (s32 *)(arg0 + 0x84) + arg1 * 3;
    h1 = *p7C;
    h2 = *p80;
    h3 = *p84;
    row = (u8 *)(idx * 0xC);
    row += *(u32 *)(arg0 + 0x78);
    n = 0x20;
    c10 = *(s32 *)(row + 0x10);
    c14 = *(s32 *)(row + 0x14);
    c18 = *(s32 *)(row + 0x18);
    do {
        b = *p;
        hi = b >> 4;
        acc = -(c18 * h3 + (c10 * h1 + c14 * h2));
        p++;
        lo = b & 0xF;
        if (hi < 8) {
            x = (acc + hi * pos) >> 12;
        } else {
            x = (acc + (hi - 0x10) * neg) >> 12;
        }
        if (x > 0x7FFF) {
            x = 0x7FFF;
        }
        if (x < -0x8000) {
            x = -0x8000;
        }
        acc = -(c18 * h2 + (c10 * x + c14 * h1));
        if (lo < 8) {
            y = (acc + lo * pos) >> 12;
        } else {
            y = (acc + (lo - 0x10) * neg) >> 12;
        }
        if (y > 0x7FFF) {
            y = 0x7FFF;
        }
        if (y < -0x8000) {
            y = -0x8000;
        }
        out[0] = x;
        out[1] = y;
        h3 = h1;
        h2 = x;
        n -= 2;
        out += 2;
        h1 = y;
    } while (n > 0);
    *p7C = y;
    *p80 = x;
    *p84 = h3;
    return p - in;
}
