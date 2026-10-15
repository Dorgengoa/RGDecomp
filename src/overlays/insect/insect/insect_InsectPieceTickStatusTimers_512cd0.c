#include "types.h"
/* insect 0x00512CD0 -- 19 instructions, no frame.  A 7-iteration countdown
 * over a byte array at +0x3C.  The counter is an `s8` LOCAL: the decrement is
 * an `addiu`, the store an `sb`, and the second test needs the value
 * re-narrowed, which is the `dsll32/dsra32 ..,24` pair.
 *
 * The element address is held TWICE -- $3 = base+i for the load (which folds
 * +0x3C into its displacement and then reuses $3 as the value register) and
 * $5 = $3+0x3C for the two stores.  One pointer local for each. */

void insect_InsectPieceTickStatusTimers_512cd0(s8 *base)
{
    s32 i;
    s8 *e;
    s8 *q;
    s8 v;

    for (i = 0; i < 7; i++) {
        e = base + i;
        q = e + 0x3C;
        v = e[0x3C];
        if (v > 0) {
            v--;
            *q = v;
            if (v <= 0) {
                *q = 0;
            }
        }
    }
}
