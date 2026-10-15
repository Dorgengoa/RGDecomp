#include "types.h"

extern void MinimapSetFadeMode_329de0(s32, s32, f32);
extern f32 MinimapAddDrawAlpha_32a0c0(f32);
extern f32 MinimapGetDrawAlpha_32a180(s32);
extern void MinimapSetFadeAlpha_32a1d0(s32, f32);

void MinimapFadeInStep_329ff0(s32 arg0, f32 fparg0)
{
    if (fparg0 <= 0.0f) {
        MinimapSetFadeMode_329de0(arg0, 0, -1.0f);
        MinimapSetFadeAlpha_32a1d0(arg0, 1.0f);
        return;
    }
    MinimapSetFadeAlpha_32a1d0(arg0, MinimapAddDrawAlpha_32a0c0(1.0f / fparg0));
    if (!(MinimapGetDrawAlpha_32a180(arg0) < 1.0f)) {
        MinimapSetFadeMode_329de0(arg0, 0, -1.0f);
        MinimapSetFadeAlpha_32a1d0(arg0, 1.0f);
    }
}
