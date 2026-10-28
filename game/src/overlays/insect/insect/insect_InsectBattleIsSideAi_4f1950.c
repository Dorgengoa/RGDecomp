/* rgp:protos */
#define RGP_SELF_insect_InsectBattleIsSideAi_4f1950 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F1950 -- 48 bytes, 12 instructions.  Two separate calls, not one
 * call with a normalised flag: the `bnez $5` fall-through is the ZERO arm, so
 * the source tests `== 0` first. */

/*rgp*/

int insect_InsectBattleIsSideAi_4f1950(void *o, s32 f)
{ int rgp_v0 = 0;
    if (f == 0) {
        (rgp_v0 = insect_InsectBattleTestFlag_50da40(o, 0));
    } else {
        (rgp_v0 = insect_InsectBattleTestFlag_50da40(o, 1));
    }
return rgp_v0; }
