/* rgp:protos */
#define RGP_SELF_title_TitleSceneOverlayModeOff_4eaa00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EAA00 -- two call pairs, each feeding its result
 * straight into the next call's first argument. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void title_TitleSceneOverlayModeOff_4eaa00(void)
{
    GameSceneSetTimeScaleLockedMaybe_1ceb90(GetCurrentScene_1f5be0(), 0);
    DrawEnvSetVsyncInterval_144140(GetDrawCtx_15de80(), 2, 0);
}
