#include "types.h"

/* MAIN SceneScreenOverlayResetAllMaybe_2f1f00 -- sibling of GameSceneCBlurResetMode2Maybe_2f1da0.  The loop runs 0..0xDF
   and is entered unconditionally.  ScreenFadeSetOverlayZoomMaybe_1cf530 / GameSceneObjSetCBlurMaybe_1cf900 take
   their floats in $f12.. and their integers in $4.. (independent PS2
   EABI pools), so the C parameter ORDER below is only a spelling. */

extern void *GetCurrentScene_1f5be0(void);
extern void ScreenFadeSetOverlayMaybe_1cf540(void *, s32, s32, s32);
extern void ScreenFadeSetOverlayZoomMaybe_1cf530(void *, f32, f32, f32);
extern void ObjRecClearFlags_1c3dc0(void *, s32, s32, s32);
extern void GameSceneObjSetCBlurMaybe_1cf900(void *, s32, s32, f32);
extern f32 D_0047DD1C;

void SceneScreenOverlayResetAllMaybe_2f1f00(void)
{
    s32 i;
    u8 *o;

    o = GetCurrentScene_1f5be0();
    ScreenFadeSetOverlayMaybe_1cf540(o, 0x64, 0, 0);
    ScreenFadeSetOverlayZoomMaybe_1cf530(o, D_0047DD1C, 256.0f, 224.0f);
    *(s16 *)(o + 0x58B4) = 0;
    *(s16 *)(o + 0x58B6) = 0;
    for (i = 0; i < 0xE0; i++) {
        ObjRecClearFlags_1c3dc0(o, 1, i, 0x2000000);
        GameSceneObjSetCBlurMaybe_1cf900(o, i, 0, 1.0f);
    }
}
