#include "types.h"

void MesWinSetLineWidth_273be0(s32 p0, s32 p1, s32 p2)
{
    if (p2 >= 0) {
        if (p1 >= 0) {
            if (p1 < 0x14) {
                goto ok;
            }
        }
    }
    return;
ok:
    *(s16 *)((u8 *)(p1 << 1) + p0 + 0x1D74) = p2;
}
