#include "types.h"

void HpGaugeTickHops_31e550(s32 p0)
{
    s32 l0;
    s8 *q;
    s8 t0;
    s8 t1;

    l0 = 0;
    do {
        q = (s8 *)(p0 + l0 + 0x210);
        t0 = *(s8 *)((u8 *)(p0 + l0) + 0x210);
        if (t0 > 0) {
            t1 = t0 - 1;
            *q = t1;
            if (t1 <= 0) {
                *q = 0;
            }
        }
        l0 = (l0 + 1);
    } while (l0 < 0x10);
}
