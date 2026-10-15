#include "types.h"
/* insmenu 0x4ED950 -- latch a gp byte flag from a predicate, return 1.
 *
 * `beql $2, $0, L` branches AWAY on the == 0 case carrying that
 * arm's `sb $0` in its delay slot, so the FALL-THROUGH is the
 * != 0 arm and the source condition is the POSITIVE one.
 * Retail materialises `addiu $2, $0, 1` TWICE, once per arm, so
 * the `return 1` belongs INSIDE both arms. */
extern s32 insmenu_InsectVsTwoPlayerPanelIsVisible_4f1b20(void);
extern u8 D_00484304;
s32 insmenu_InsectVsStateWaitFade_4ed950(void)
{
    if (insmenu_InsectVsTwoPlayerPanelIsVisible_4f1b20() != 0) { D_00484304 = 1; return 1; }
    D_00484304 = 0;
    return 1;
}
