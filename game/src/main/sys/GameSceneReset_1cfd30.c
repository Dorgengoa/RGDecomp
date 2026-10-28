/* rgp:protos */
#define RGP_SELF_GameSceneReset_1cfd30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x59D0];
    s32 m59D0;
    s32 m59D4;
    s32 m59D8;
    s32 m59DC;
    u8 pad59E0[0x41C];
    s32 m5DFC;
    u8 pad5E00[0x575C];
    s32 mB55C;
};

void GameSceneReset_1cfd30(struct Obj0 *p0)
{
    s32 r4;
    s32 r5;

    ParamTableResetAllMaybe_1cfc00(p0);
    CBlurParamsInit_1ce6e0((struct Obj0 *)((u8 *)p0 + 0x58A0));
    GameSceneDoorGlareInit_1cf7c0(p0);
    GameSceneDofReset_1cf200(p0);
    r4 = ScreenFadeInit_1cf770(p0);
    p0->m59D0 = 0x42A00000;
    p0->m59D4 = 0x42A00000;
    p0->m59D8 = 0;
    p0->m59DC = 0;
    r5 = ((s32)ParticleSwirlReset_17d750((struct Obj0 *)((u8 *)p0 + 0x59E0)));
    p0->mB55C = 0xBF800000;
    p0->m5DFC = 0;
    SceneReset_1c4610(p0);
}
