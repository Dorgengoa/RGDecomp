/* rgp:protos */
#define RGP_SELF_GameSceneCBlurResetMode2Maybe_2f1da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN GameSceneCBlurResetMode2Maybe_2f1da0 -- neighbour of GameSceneCBlurReset_2f1e20/SceneScreenOverlayResetAllMaybe_2f1f00: same
   GetCurrentScene_1f5be0 handle, same +0x58A0 sub-object, same
   ColorFromRgba128_1ce5f0(sub, 0x80, 0x80, 0x80, 0x80).
   The two `sh 0` are written through the BASE (+0x58B4/+0x58B6), the
   two later stores through the SUB (+0x11/+0x12) -- that is how retail
   addresses them, so the source keeps both handles. */

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047DCF4;

void GameSceneCBlurResetMode2Maybe_2f1da0(void)
{
    u8 *o;
    u8 *q;

    o = GetCurrentScene_1f5be0();
    GameSceneSoundSetPollHold_1d1180(o, 0);
    *(f32 *)(o + 0x5930) = D_0047DCF4;
    q = o + 0x58A0;
    *(s16 *)(o + 0x58B4) = 0;
    *(s16 *)(o + 0x58B6) = 0;
    ColorFromRgba128_1ce5f0(q, 0x80, 0x80, 0x80, 0x80);
    *(s16 *)(q + 0x12) = 2;
    *(u8 *)(q + 0x11) = 1;
}
