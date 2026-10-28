/* rgp:protos */
#define RGP_SELF_MinimapFadeInStep_329ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MinimapFadeInStep_329ff0(s32 arg0, f32 fparg0)
{
    if (fparg0 <= 0.0f) {
        MinimapSetFadeMode_329de0(arg0, 0, -1.0f);
        MinimapSetFadeAlpha_32a1d0(arg0, 1.0f);
        return;
    }
    MinimapSetFadeAlpha_32a1d0(arg0, MinimapAddDrawAlpha_32a0c0((int)arg0, 1.0f / fparg0));
    if (!(MinimapGetDrawAlpha_32a180(arg0) < 1.0f)) {
        MinimapSetFadeMode_329de0(arg0, 0, -1.0f);
        MinimapSetFadeAlpha_32a1d0(arg0, 1.0f);
    }
}
