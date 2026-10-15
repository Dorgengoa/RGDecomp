#include "types.h"
/* insect 0x005229E0 -- 100 bytes, 25 instructions.
 * A 5-slot ring: fill the first free slot, else shift down and append. */

s32 insect_InsectAiPushState_5229e0(s32 *a, s32 v)
{
    s32 i;

    for (i = 0; i < 5; i++) {
        if (a[i] == -1) {
            a[i] = v;
            return 1;
        }
    }
    for (i = 0; i < 4; i++) {
        a[i] = a[i + 1];
    }
    a[4] = v;
    return 0;
}
