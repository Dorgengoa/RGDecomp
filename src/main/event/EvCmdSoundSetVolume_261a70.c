#include "types.h"
#pragma no_branch_likely on

void GameSceneSoundFadeVolume_1d0370(s32, f32, s32);                   /* extern */
void GameSceneSoundSetVolumeNow_1d0400(s32, f32);                        /* extern */
void GameSceneSoundSlot4FadeTo_1d0610(s32, f32, s32);                   /* extern */
void GameSceneSoundSlot4SetVolume_1d0630(s32, f32);                        /* extern */
f32 TaggedGetFloat_26a280(s32);                                 /* extern */
s32 ScriptGetInt_26a2a0(s32);                              /* extern */
extern s32 D_00481F78;

s32 EvCmdSoundSetVolume_261a70(s64 *arg0, s32 arg1) {
        s32 arg_h1;

    f32 temp_f20;
    s32 temp_2;

    temp_f20 = TaggedGetFloat_26a280((s32)arg0++);
    if (arg1 == 1) {
        GameSceneSoundSetVolumeNow_1d0400(D_00481F78, temp_f20);
        GameSceneSoundSlot4SetVolume_1d0630(D_00481F78, temp_f20);
    } else if (arg1 == 2) {
        temp_2 = ScriptGetInt_26a2a0((s32)arg0);
        GameSceneSoundFadeVolume_1d0370(D_00481F78, temp_f20, temp_2);
        GameSceneSoundSlot4FadeTo_1d0610(D_00481F78, temp_f20, temp_2);
    }
    return 1;
}
