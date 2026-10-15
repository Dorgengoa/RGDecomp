#include "types.h"

s32 GameRecGetInsectRecSlot_3ce090(s32 p0, s32 p1)
{
    if (p1 >= 0) {
        if (p1 < 3) {
            goto ok;
        }
    }
    return 0;
ok:
    return ((p0 + (p1 * 0x84C)) + 0x1ADC);
}
