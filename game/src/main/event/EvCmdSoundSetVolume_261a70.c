/* rgp:protos */
#define RGP_SELF_EvCmdSoundSetVolume_261a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma no_branch_likely on

/*rgp*/                   /* extern */
/*rgp*/                        /* extern */
/*rgp*/                   /* extern */
/*rgp*/                        /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                              /* extern */
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
        GameSceneSoundFadeVolume_1d0370(D_00481F78, temp_2, temp_f20);
        GameSceneSoundSlot4FadeTo_1d0610(D_00481F78, temp_2, temp_f20);
    }
    return 1;
}
