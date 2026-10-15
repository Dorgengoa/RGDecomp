#include "types.h"
/* insect 0x00510BA0 -- 40 bytes, 10 instructions.  The `beql $2,$0,<epilogue>`
 * with `daddu $2,$0,$0` in the delay slot is the TRAILING `return 0`. */

extern s32 *insect_InsectHelpGetEntry_510c00(void);

s32 insect_InsectHelpGetEntryTitle_510ba0(void)
{
    s32 *p;

    p = insect_InsectHelpGetEntry_510c00();
    if (p != 0) {
        return *p;
    }
    return 0;
}
