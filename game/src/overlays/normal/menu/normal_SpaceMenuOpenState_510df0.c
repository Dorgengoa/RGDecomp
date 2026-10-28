/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuOpenState_510df0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510DF0 -- guarded pair, tail of the phase-handler family. */

extern void *D_004846B8;          /* gp - 0xAB8 */
extern void *D_004846B4;          /* gp - 0xABC */

/*rgp*/
/*rgp*/

s32 normal_SpaceMenuOpenState_510df0(void *a, s32 b)
{
    if (b != 0) {
        normal_SpaceMenuBuild_514560(D_004846B8);
        StateMachineSetState_28ede0(D_004846B4, 5, 1);
    }
    return 1;
}
