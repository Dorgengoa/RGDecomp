/* rgp:protos */
#define RGP_SELF_normal_TransMenuBobIconShow_5183c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005183C0 -- the two-widget publish pair.  Both guards test a gp
 * handle for NULL and make the SAME call; retail's second `lw -0xA60` in the
 * first beql's delay slot is the branch-likely copy of the second guard's
 * load, not a CSE.  `andi $6,$16,0xFF` is the u8 parameter slot. */

extern void *D_004846E8;   /* gp - 0xA88 */
extern void *D_00484710;   /* gp - 0xA60 */

/*rgp*/

void normal_TransMenuBobIconShow_5183c0(s32 a)
{
    if (D_004846E8 != NULL) {
        UiSetWidgetsVisibleById_291110(D_004846E8, 0x75D1, a, 1);
    }
    if (D_00484710 != NULL) {
        UiSetWidgetsVisibleById_291110(D_00484710, 0x75D1, a, 1);
    }
}
