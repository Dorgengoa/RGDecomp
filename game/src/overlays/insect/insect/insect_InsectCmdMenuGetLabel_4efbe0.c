/* rgp:protos */
#define RGP_SELF_insect_InsectCmdMenuGetLabel_4efbe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFBE0 -- 40 bytes, 10 instructions.  The POSITIVE guard is what
 * folds the `return 0` into the `beql $2, $0, <epilogue>` delay slot; the
 * `if (p == 0) return 0;` polarity costs a word. */

/*rgp*/

s32 insect_InsectCmdMenuGetLabel_4efbe0(void *rgp_a0, int rgp_a1)
{
    s32 *p;

    p = ((s32 *)insect_InsectCmdMenuGetEntry_4efc50((void *)rgp_a0, (int)rgp_a1));
    if (p != 0) {
        return *p;
    }
    return 0;
}
