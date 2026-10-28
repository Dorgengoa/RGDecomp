/* rgp:protos */
#define RGP_SELF_insect_InsectBoardInBounds_4efac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFAC0 -- 60 bytes, 15 instructions, 4 conditional branches, no
 * stores.  A bounds test on a 5x7 grid; $4 is never read, so the object
 * pointer is a dead `this`. */

s32 insect_InsectBoardInBounds_4efac0(void *o, long long col, long long row)
{
    if (col >= 0 && row >= 0 && col < 5 && row < 7) {
        return 1;
    }
    return 0;
}
