/* rgp:protos */
#define RGP_SELF_GameSceneSoundUpdate_1d0860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T1d0860 {
    u8 pad0[0xB0A4];
    u8 xB0A4[0xC];
    u8 xB0B0[7][0x88];
    u8 padB4A8[0xB4AC - 0xB0B0 - 7 * 0x88];
    f32 xB4AC;
    f32 xB4B0;
    f32 xB4B4;
} T1d0860;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void GameSceneSoundUpdate_1d0860(T1d0860 *arg0)
{
    u8 *p;
    s32 i;
    f32 f;

    GameSceneAmbientSwitchSlot_1d0220((void *)arg0);
    if (arg0->xB4B4 != 0.0f) {
        arg0->xB4AC = arg0->xB4AC + arg0->xB4B4 * GameSceneGetTimeStep_1ceba0(arg0);
        if (!(arg0->xB4B4 <= 0.0f)) {
            if (!(arg0->xB4AC < arg0->xB4B0)) {
                arg0->xB4AC = arg0->xB4B0;
                arg0->xB4B4 = 0.0f;
            }
        }
        if (arg0->xB4B4 < 0.0f) {
            if (arg0->xB4AC <= arg0->xB4B0) {
                arg0->xB4AC = arg0->xB4B0;
                arg0->xB4B4 = 0.0f;
            }
        }
    }
    p = arg0->xB0B0[0];
    for (i = 0; i < 7; i++, p += 0x88) {
        if (((short)SoundSlotGetIndex_1d2140(p)) == 2 || ((short)SoundSlotGetIndex_1d2140(p)) == 3) {
            SoundSlotUpdateVolumeFade_1d1af0(p, arg0->xB4AC * GameSceneSoundGetOptionVolume_1d1200(arg0));
        } else {
            SoundSlotUpdateVolumeFade_1d1af0(p, GameSceneSoundGetOptionVolume_1d1200(arg0));
        }
    }
    GameSceneEmitterSoundsUpdate_1cfde0(arg0);
    if (GameSceneSoundIsMutedMaybe_1d11c0(arg0) != 0) {
        f = 0.0f;
    } else {
        f = GameSceneSoundGetVolumeScale_1d11e0(arg0) * GameSceneSoundGetOptionVolume_1d1200(arg0);
    }
    SoundSetCategoryVolume_1bb230(7, f);
    SoundSetCategoryVolume_1bb230(5, f);
    SoundNoteListUpdate_1b4b60(arg0->xB0A4);
}
