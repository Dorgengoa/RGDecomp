#include "types.h"

struct Sub0 {
    s32 m0;
    s32 m4;
};

s32 PadIsRepeatTriggered_183dd0(u8 *p0, s32 p1)
{
    struct Sub0 *q;
    s32 i;
    s32 mask;

    q = (struct Sub0 *)(p0 + 0xC0);
    mask = 1;
    i = 0;
    while (i < 0x20) {
        if ((p1 & mask) != 0) {
            if ((q->m4 & mask) != 0) {
                return 1;
            }
        }
        i++;
        mask = mask << 1;
    }
    return 0;
}
