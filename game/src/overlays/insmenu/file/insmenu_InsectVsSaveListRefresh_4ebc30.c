/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveListRefresh_4ebc30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EBC30 (172 bytes) -- dispatch on the second value the scene
 * lookup returns.
 *
 * ★ The compare chain runs 4, 3, 2, 1 while the blocks are laid out 1, 2, 3, 4:
 * the source is an if/else-if chain in the COMPARE order and mwcc lays the arms
 * out reversed.
 * ★ Each `beql` carries `daddu $4, $16, $0` in its delay slot -- one argument
 * setup duplicated into every likely slot, not four separate stores. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsSaveListRefresh_4ebc30(s32 a, s32 b)
{
    s16 kind;
    s16 x;

    insmenu_InsectVsSaveKindLookup_4ebd90(&x, &kind);
    switch (kind) {
    case 1:
        SaveSlotListRefresh_377ae0(a);
        break;
    case 2:
        InsectVsSaveSlotListRefreshMaybe_37ab70(a);
        break;
    case 3:
        InsectVsTeamListRefreshMaybe_37a2b0(a);
        break;
    case 4:
        SaveSlotListRefreshDetailMaybe_3783c0(a, b);
        break;
    }
}
