/* PARK: m2c cannot decompile -- "Found jr instruction ... but the
   corresponding jump table is not provided." Needs a jump-table
   reconstruction pass this lane's budget does not cover. Not attempted. */
/* s49m: MATCH (jtbl, rodata_check) */
#include "types.h"

typedef void (*CbFn)(u8 *, u8 *, s32, s32);
extern void *memcpy(void *, const void *, u32);

s32 VariantSetRaw_36ee90(u8 *self, u32 type, void *src, s32 notify)
{
    s32 n;
    s32 t;
    CbFn fn;

    if (src == 0) {
        return 0;
    }
    n = 0;
    t = type & 0xF;
    *(s32 *)self = t;
    switch (t) {
    case 1:
        n = 1;
        memcpy(self + 8, src, n);
        break;
    case 2:
        n = 1;
        memcpy(self + 8, src, n);
        break;
    case 3:
        n = 2;
        memcpy(self + 8, src, n);
        break;
    case 4:
        n = 2;
        memcpy(self + 8, src, n);
        break;
    case 5:
        n = 4;
        memcpy(self + 8, src, n);
        break;
    case 6:
        n = 4;
        memcpy(self + 8, src, n);
        break;
    case 7:
        n = 8;
        memcpy(self + 8, src, n);
        break;
    case 8:
        n = 8;
        memcpy(self + 8, src, n);
        break;
    case 9:
        n = 4;
        memcpy(self + 8, src, n);
        break;
    case 10:
        n = 8;
        memcpy(self + 8, src, n);
        break;
    }
    if (notify != 0) {
        fn = *(CbFn *)(self + 0x20);
        if (fn != 0) {
            fn(self, self + 0x28, 0, 0);
        }
    }
    return n;
}
