/* rgp:protos */
#define RGP_SELF_title_FUN_004eaa80 1
#define RGP_SELF_title_TitleSceneOverlayModeOn_4eaa40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EAA40.  Second of the three slots that hold TWO
 * functions -- Ghidra missed the one at 0x004EAA80 and the previous symbol
 * absorbed it.  Both are written here, in address order.
 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void title_TitleSceneOverlayModeOn_4eaa40(void)
{
    DrawEnvSetVsyncInterval_144140(GetDrawCtx_15de80(), 1, 0);
    GameSceneSetTimeScaleLockedMaybe_1ceb90(GetCurrentScene_1f5be0(), 1);
}

s32 title_FUN_004eaa80(void)
{
    return 1;
}
