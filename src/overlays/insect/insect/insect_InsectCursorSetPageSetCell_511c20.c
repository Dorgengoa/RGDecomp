#include "types.h"
/* insect 0x00511C20 -- 9 instructions, no frame.  The `beql` tail-duplicates
 * the unconditional `p->m8 = a` into its delay slot; the four clears are the
 * guarded body.  $4 is never read: the first parameter is unused. */

typedef struct Slot {
    u8 pad00[0x8];
    s8 m8;                          /* +0x08 */
    s8 m9;                          /* +0x09 */
    s8 mA;                          /* +0x0A */
    s8 mB;                          /* +0x0B */
} Slot;

void insect_InsectCursorSetPageSetCell_511c20(void *unused, Slot *p, s8 a, s8 b)
{
    if (p != 0) {
        p->m9 = 0;
        p->m8 = 0;
        p->mB = 0;
        p->mA = 0;
    }
    p->m8 = a;
    p->m9 = b;
}
