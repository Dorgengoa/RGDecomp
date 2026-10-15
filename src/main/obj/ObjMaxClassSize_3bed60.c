#include "types.h"

extern const s32 D_00454630[];

s32 ObjMaxClassSize_3bed60(void)
{
    s32 a[5];
    s32 best;
    s32 i;
    s32 v;
    const s32 *s;
    s32 *d;
    s32 n;

    s = D_00454630;
    d = a;
    n = 5;
    do {
        *d = *s;
        n--;
        s++;
        d++;
    } while (n > 0);

    best = 0;
    i = 0;
    while (1) {
        v = a[i];
        if (v <= 0) {
            break;
        }
        if (best < v) {
            best = v;
        }
        i = i + 1;
    }
    return best;
}
