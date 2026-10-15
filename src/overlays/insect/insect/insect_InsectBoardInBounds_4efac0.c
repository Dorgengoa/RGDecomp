#include "types.h"
/* insect 0x004EFAC0 -- 60 bytes, 15 instructions, 4 conditional branches, no
 * stores.  A bounds test on a 5x7 grid; $4 is never read, so the object
 * pointer is a dead `this`. */

s32 insect_InsectBoardInBounds_4efac0(void *o, s32 col, s32 row)
{
    if (col >= 0 && row >= 0 && col < 5 && row < 7) {
        return 1;
    }
    return 0;
}
