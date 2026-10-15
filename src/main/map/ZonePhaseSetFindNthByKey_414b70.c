#include "types.h"

#pragma divbyzerocheck on

s32 *ZonePhaseSetFindNthByKey_414b70(void *arg0, s16 arg1, s16 arg2, s32 arg3)
{
    s16 a = arg1;
    s16 b = arg2;
    s32 k;
    s32 i;
    s32 n;
    s32 *p;
    s32 v;

    if (a < 0 || b < 0 || arg3 < 0) {
        return NULL;
    }
    n = *(s16 *)((u8 *)arg0 + 0x7C);
    if (n <= 0) {
        return NULL;
    }
    p = *(s32 **)((u8 *)arg0 + 0x8C);
    if (p == NULL) {
        return NULL;
    }

    k = 0;
    for (i = 0; i < n; i++, p += 2) {
        v = *p;
        if (a == (v / 10000000) % 100 && b == (v / 100000) % 10000) {
            if (k == arg3) {
                return p;
            }
            k++;
        }
    }

    return NULL;
}
