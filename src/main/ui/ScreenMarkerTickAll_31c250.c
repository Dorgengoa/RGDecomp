#include "types.h"

extern void ScreenMarkerSlotTick_31c190(s32, s32);

void ScreenMarkerTickAll_31c250(s32 p0)
{
    s32 l0;
    s32 b;
    s16 *q;

    l0 = 0;
    do {
        b = p0 + (l0 << 1);
        q = (s16 *)(b + 0xE0);
        if (*(s16 *)(b + 0xE0) > 0) {
            *q = *q - 1;
        }
        if (*q <= 0) {
            ScreenMarkerSlotTick_31c190(p0, l0);
        }
        l0 = (l0 + 1);
    } while (l0 < 0x20);
}
