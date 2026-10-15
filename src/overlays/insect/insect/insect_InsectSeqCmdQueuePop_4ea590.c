#include "types.h"
/* insect 0x004EA590 -- 40 bytes, 10 instructions, leaf.  Shift the 0x40-word
 * ring at +0x5C down by one and clear the last slot; the trailing `sw $0,
 * 0x158($4)` rides the `jr $31` delay slot. */

typedef struct Obj {
    u8  pad00[0x5C];
    s32 f5C[0x40];                  /* +0x5C */
    s32 f15C;                       /* +0x15C */
} Obj;

void insect_InsectSeqCmdQueuePop_4ea590(Obj *o)
{
    s32 i;

    for (i = 0; i < 0x3F; i++) {
        o->f5C[i] = o->f5C[i + 1];
    }
    o->f5C[0x3F] = 0;
}
