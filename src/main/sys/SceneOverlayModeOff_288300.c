#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern void GameSceneSetTimeScaleLockedMaybe_1ceb90(s32, s32);
extern s32 GetDrawCtx_15de80(void);
extern void DrawEnvSetVsyncInterval_144140(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SceneOverlayModeOff_288300(void)
{
    s32 r0;
    s32 r2;

    r0 = GetCurrentScene_1f5be0();
    GameSceneSetTimeScaleLockedMaybe_1ceb90(r0, 0);
    r2 = GetDrawCtx_15de80();
    DrawEnvSetVsyncInterval_144140(r2, 2, 0);
}
