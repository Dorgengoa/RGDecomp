#pragma optimization_level 3
#include "types.h"
/* insect 0x00513FA0 -- 120 bytes, 30 instructions, no calls.
 * Remove-and-shift over a 5-entry s8 array at +0x0F.
 *
 * The `#pragma optimization_level 3` is the WHOLE match (insect session 51).
 * At the file default (-O4) mwcc HOISTS this loop's single-use literal 1 into
 * the preheader and copies it in the body -- 31 instructions for retail's 30 --
 * and the park's `found++` is the right length with `addiu $t1,$t1,1` for
 * retail's `addiu $t1,$zero,1`.  -O3 rematerialises the constant in place.
 * Ported from factory session 38's arm U1 on factory_FactoryMarkerDrawNumber_4f5710, whose header
 * records the identical residue and fix; see [[levers.d/mwcc-optimization-level]].
 * ARMED: `#pragma optimization_leveL 3` (bogus name) reproduces the -O4 object
 * exactly, and levels 0/1/2/4 are four further distinct wrong objects.
 */

void insect_InsectTeamSlotPlaceOrderRemove_513fa0(s8 *p, s32 v)
{
    s32 found;
    s32 i;
    s32 c;

    found = 0;
    i = 0;
    do {
        if (found == 0) {
            c = p[i + 0xF];
            if (c == v) {
                p[i + 0xF] = -1;
                found = 1;
            }
        }
        if (found != 0) {
            if (i + 1 < 5) {
                p[i + 0xF] = p[i + 0x10];
                p[i + 0x10] = -1;
            } else {
                p[i + 0xF] = -1;
            }
        }
        i++;
    } while (i < 5);
}
