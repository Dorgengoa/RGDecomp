#include "types.h"

void LightningStopByOwner_2d7190(s32 p0, s32 p1)
{
    s32 l0;
    s32 e;
    s16 *q;

    l0 = 0;
    do {
        e = p0 + (l0 * 0x30);
        q = (s16 *)(e + 0x3A);
        if (*q != 0) {
            if (*(s16 *)(e + 0x30) == p1) {
                *q = 0;
            }
        }
        l0 = (l0 + 1);
    } while (l0 < 0x10);
}
