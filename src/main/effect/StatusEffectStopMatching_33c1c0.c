#include "types.h"

/* Scan sixteen 0xE0-byte records hanging off *p0; the first one the probe
   accepts is handed to the consumer and the scan returns.  Retail's loop is
   the test-at-the-bottom form (b to the slti) and the i++ lives in the beql
   delay slot, which is the loop increment duplicated onto the continue edge.
   Note the probe's last two arguments are the caller's SWAPPED. */

extern s32 StatusEffectSlotMatches_33d410(u8 *, s32, s32);
extern void StatusEffectSlotStop_33c2b0(u8 *);

void StatusEffectStopMatching_33c1c0(u8 **p0, s32 p1, s32 p2)
{
    u8 *cur;
    s32 i;

    cur = *p0;
    for (i = 0; i < 0x10; i++, cur += 0xE0) {
        if (StatusEffectSlotMatches_33d410(cur, p2, p1) != 0) {
            StatusEffectSlotStop_33c2b0(cur);
            return;
        }
    }
}
