/* rgp:protos */
#define RGP_SELF_normal_TransMenuBobTimerTick_518540 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518540 -- tail call.  D_0047D93C is a gp float in MAIN's pool
 * region but it is spelled as an EXTERN, not a literal: the sibling site at
 * 0x0047D3B8 holds the SAME value, so a literal would share one .lit4 entry
 * and could not reproduce two distinct displacements. */

extern f32 D_00484790;   /* gp - 0x9E0   */
extern f32 D_0047D93C;   /* gp - 0x7834  */

/*rgp*/

void normal_TransMenuBobTimerTick_518540(void)
{
    PhaseAdvanceWrapPi_28b630(&D_00484790, D_0047D93C);
}
