/* rgp:protos */
#define RGP_SELF_insect_InsectHelpGetEntryTitle_510ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510BA0 -- 40 bytes, 10 instructions.  The `beql $2,$0,<epilogue>`
 * with `daddu $2,$0,$0` in the delay slot is the TRAILING `return 0`. */

/*rgp*/

s32 insect_InsectHelpGetEntryTitle_510ba0(void *rgp_a0, int rgp_a1)
{
    s32 *p;

    p = ((s32 *)insect_InsectHelpGetEntry_510c00((void *)rgp_a0, (int)rgp_a1));
    if (p != 0) {
        return *p;
    }
    return 0;
}
