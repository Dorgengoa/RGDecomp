#include "types.h"
typedef struct { s32 a, b; } E8_1927c0;
extern s32 VariantGetInt_15f780(E8_1927c0 *);
struct S1927c0 { u8 pad000[0x1BC]; s32 arr[1]; };
extern struct S1927c0 *D_004812F4;

s32 MapSceneCfgDofTime_1927c0(E8_1927c0 *p0, s32 p1)
{
    s32 n;
    s32 i;

    n = 4;
    if (p1 < 4) {
        n = p1;
    }
    i = 0;
    while (i < n) {
        D_004812F4->arr[i] = VariantGetInt_15f780(p0++);
        i = i + 1;
    }
    return 1;
}
