/* rgp:protos */
#define RGP_SELF_InsectCageMenuItemGridRefresh_38f790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482374;

void InsectCageMenuItemGridRefresh_38f790(s32 p0, s32 p1, s32 p2)
{
    s32 t0;

    MenuItemModeApplyMaybe_2b36e0(p0, 0, 1);
    t0 = D_00482374;
    MenuDrawItemTabs_2a4ee0(t0, 0x67, 0);
    InsectCageMenuItemGridSetStates_38f920(p0, 1);
    InsectCageMenuItemCellSetupMaybe_38f810(p1, p0);
    if (p2 != 0) {
        PlayMenuSe_289ef0(0xB);
    }
}
