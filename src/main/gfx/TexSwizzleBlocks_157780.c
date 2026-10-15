#include "types.h"

extern u8 *OperatorNewArray_100900(s32 size);
extern void OperatorDeleteArray_100820(void *p);
extern void *memset(void *d, s32 c, u32 n);
extern void *memcpy(void *d, const void *s, u32 n);
extern void TexSwizzleTile_157a30(s32 w, s32 h, u8 *src, u8 *dst);

s32 TexSwizzleBlocks_157780(s32 w, s32 h, u8 *data) {
    u8 tmpA[0x2000];
    u8 tmpB[0x2000];
    u8 *volatile mem;
    s32 by;
    s32 bx;
    s32 k;
    s32 rowb;
    s32 bw;
    u8 *buf;
    u8 *d2;
    u8 *s2;
    u8 *orow;
    s32 half;
    s32 nx;
    s32 bh;
    u8 *src;
    u8 *dst;
    s32 size;
    s32 ny;
    s32 j;
    u8 *irow;

    buf = OperatorNewArray_100900(0x10000);
    mem = buf;
    size = w * h;
    if (size > 0x10000) {
        OperatorDeleteArray_100820(buf);
        return 0;
    }
    memset(tmpA, 0, 0x2000);
    memset(tmpB, 0, 0x2000);
    nx = (w - 1) / 128 + 1;
    ny = (h - 1) / 64 + 1;
    if (nx == 1) {
        bw = w;
        rowb = w * 2;
    } else {
        bw = 0x80;
        rowb = 0x100;
    }
    if (ny == 1) {
        bh = h;
        half = h / 2;
    } else {
        bh = 0x40;
        half = 0x20;
    }
    for (by = 0; by < ny; by++) {
        for (bx = 0; bx < nx; bx++) {
            dst = tmpB;
            src = data + by * (nx * (rowb * half)) + rowb * bx;
            for (k = 0; k < half; k++) {
                memcpy(dst, src, rowb);
                src += rowb * nx;
                dst += 0x100;
            }
            TexSwizzleTile_157a30(0x80, 0x40, tmpB, tmpA);
            s2 = tmpA;
            d2 = buf + by * (nx * (bw << 6)) + bw * bx;
            for (j = 0; j < bh; j++) {
                memcpy(d2, s2, bw);
                d2 += bw * nx;
                s2 += 0x80;
            }
        }
    }
    memcpy(data, buf, size);
    OperatorDeleteArray_100820(mem);
    return 1;
}
