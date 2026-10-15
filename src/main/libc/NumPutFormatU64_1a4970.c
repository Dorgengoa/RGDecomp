#include "types.h"

typedef struct {
    u8 pad[0x38];
    s16 flags;
} Ios;

u64 UModDi3_13a430(u64, u64);
u64 UDivDi3_139eb0(u64, u64);

s32 NumPutFormatU64_1a4970(Ios *arg0, u64 val, s8 *buf) {
    s32 fl;
    u32 base;
    u16 bf;
    s8 *p;
    u64 b;
    s32 upper;
    u64 r;
    s8 c;
    s8 *q;
    s8 *e;
    s8 t;

    if (val == 0) {
        *buf = 0x30;
        return 1;
    }
    fl = arg0->flags;
    base = 10;
    switch ((u16)((u16)fl & 0x4A)) {
    case 0x40:
        base = 8;
        break;
    case 8:
        base = 16;
        break;
    }
    b = base;
    upper = (u16)((u16)(u32)fl & 0x4000) != 0;
    p = buf;
    while (val != 0) {
        r = UModDi3_13a430(val, b);
        if (r < 10) {
            c = r + 0x30;
        } else if (upper) {
            c = r + 0x37;
        } else {
            c = r + 0x57;
        }
        *p++ = c;
        val = UDivDi3_139eb0(val, b);
    }
    e = p;
    q = buf;
    if (q != e) {
        while (q < --e) {
            t = *q;
            *q = *e;
            *e = t;
            q++;
        }
    }
    return p - buf;
}
