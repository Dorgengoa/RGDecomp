#include "types.h"

extern void VariantInit_36ff00(u8 *e);

u8 *VariantPoolAlloc_3da080(u8 *p, s32 flag)
{
    s16 n;
    u8 *e;

    n = *(s16 *)(p + 0xE08);
    if (n < 0x40) {
        *(s16 *)(p + 0xE08) = n + 1;
        e = p + n * 56 + 8;
        if (flag == 0) {
            VariantInit_36ff00(e);
        }
        return e;
    }
    return 0;
}
