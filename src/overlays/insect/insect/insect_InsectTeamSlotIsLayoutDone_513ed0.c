#include "types.h"
/* insect 0x00513ED0 -- 14 instructions.  A five-slot scan on a BYTE stride:
 * `addu $2,$4,$5` with the index unscaled, then `lbu 0xA($2)`, so the +0xA is
 * part of the index and the array element is one byte wide. */

s32 insect_InsectTeamSlotIsLayoutDone_513ed0(u8 *a)
{
    s32 i;

    for (i = 0; i < 5; i++) {
        if (a[i + 0xA] == 0xFF) {
            return 0;
        }
    }
    return 1;
}
