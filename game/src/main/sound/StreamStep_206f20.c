/* rgp:protos */
#define RGP_SELF_StreamStep_206f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

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
/*rgp*/

extern s16 D_00481C84;
extern s16 D_00481C88;
extern u8 D_00481C8C;

void StreamStep_206f20(void) {
    f32 temp_f20;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;

    temp_f20 = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    temp_2 = ((s32)GetStreamMgr_207ea0());
    StreamMgrUpdate_1d6940(temp_2, temp_f20);
    if ((D_00481C84 != D_00481C88) && (StreamMgrChanIsFading_1d6360(temp_2, 0) == 0)) {
        BgmPlayTrackIfChangedMaybe_207880(D_00481C88, D_00481C8C);
    }
    temp_2_2 = ((s32)StreamMgrGetChan_1d6900(temp_2, ((short)BgmGetResumeWaitChan_207e90())));
    if (temp_2_2 != 0) {
        temp_2_3 = StreamChanGetStatus_1d6bb0(temp_2_2);
        switch (temp_2_3) {
        case 0:
        case 2:
            BgmResumeSavedTrack_207420(1);
            BgmSetResumeWaitChan_207e80(-1);
        }
    }
}
