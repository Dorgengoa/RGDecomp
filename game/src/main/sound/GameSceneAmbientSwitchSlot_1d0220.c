/* rgp:protos */
#define RGP_SELF_GameSceneAmbientSwitchSlot_1d0220 1
#include "port/game_protos.h"
#line 1
#include "types.h"


typedef struct {
    u8 pad0[0xB49C];
    s32 unkB49C;
    s32 unkB4A0;
    s32 unkB4A4;
    s8 unkB4A8;
    u8 padb4a9[0xB4B8 - 0xB4A9];
    f32 unkB4B8;
} Obj001D0220;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void GameSceneAmbientSwitchSlot_1d0220(Obj001D0220 *arg0) {
    s32 t;
    s32 v;

    if (arg0->unkB4A4 >= 0) {
        v = arg0->unkB4A8 != 2 ? 2 : 3;
        t = ((s32)GameSceneSoundSlotGet_1d0de0(arg0, v));
        if (t != 0 && ((unsigned char)SoundSlotIsLoadIdle_1d1d50(t)) != 0) {
            SoundSlotStopSe_1d1a10(t, 0);
            SoundSlotPlaySeVol_1d1ab0(t, 0, arg0->unkB4B8);
            SoundSlotFadeOut_1d1f70(((s32)GameSceneSoundSlotGet_1d0de0(arg0, arg0->unkB4A8 == 2 ? 2 : 3)), 0x1E);
            arg0->unkB49C = arg0->unkB4A0;
            arg0->unkB4A0 = arg0->unkB4A4;
            arg0->unkB4A4 = -1;
            arg0->unkB4A8 = v;
        }
    }
}
