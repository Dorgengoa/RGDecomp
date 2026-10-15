#include "types.h"

extern s32 TaskEntryOfDebugItem_208c00(s32);
extern s32 TaskTestFlag_1f57a0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 DebugTaskItemGetValue_208bd0(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = TaskEntryOfDebugItem_208c00(p0);
    if (r0 != 0) {
        r1 = TaskTestFlag_1f57a0(r0, 1);
        return r1;
    }
    return 0;
}
