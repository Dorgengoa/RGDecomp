#include "types.h"
/* insect 0x004EFBE0 -- 40 bytes, 10 instructions.  The POSITIVE guard is what
 * folds the `return 0` into the `beql $2, $0, <epilogue>` delay slot; the
 * `if (p == 0) return 0;` polarity costs a word. */

extern s32 *insect_InsectCmdMenuGetEntry_4efc50(void);

s32 insect_InsectCmdMenuGetLabel_4efbe0(void)
{
    s32 *p;

    p = insect_InsectCmdMenuGetEntry_4efc50();
    if (p != 0) {
        return *p;
    }
    return 0;
}
