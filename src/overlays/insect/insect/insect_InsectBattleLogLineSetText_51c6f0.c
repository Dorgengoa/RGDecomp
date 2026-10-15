#include "types.h"
/* insect 0x0051C6F0 -- 76 B / 19 words.  The 0051D230 clear-then-forward with
 * a null guard on the second argument.  `beql $16, $0, .L0051C72C` branches
 * INTO the exit and holds `ld $31` in its delay slot, so the FALL-THROUGH is
 * the if body: `if (b != 0) func_134A98(a, b);`.  The duplicated `ld $31` is
 * the beql tail, not a second source statement.
 * Fill length is 0x50 here (0x20 in the seed, 0x14 in 005147C0). */
extern void func_131B60(void *a, s32 v, s32 n);
extern void func_134A98(void *a, void *b);

void insect_InsectBattleLogLineSetText_51c6f0(void *a, void *b)
{
    func_131B60(a, 0, 0x50);
    if (b != 0) {
        func_134A98(a, b);
    }
}
