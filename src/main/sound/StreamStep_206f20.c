#include "types.h"
#pragma opt_common_subs off

extern f32 GameSceneGetTimeStep_1ceba0(s32 arg0);
extern s32 StreamMgrChanIsFading_1d6360(s32 arg0, s32 arg1);
extern s32 StreamMgrGetChan_1d6900(s32 arg0, s32 arg1);
extern void StreamMgrUpdate_1d6940(s32 arg0, f32 arg1);
extern s32 StreamChanGetStatus_1d6bb0(s32 arg0);
extern s32 GetCurrentScene_1f5be0(void);
extern void BgmResumeSavedTrack_207420(s32 arg0);
extern void BgmPlayTrackIfChangedMaybe_207880(s16 arg0, u8 arg1);
extern void BgmSetResumeWaitChan_207e80(s32 arg0);
extern s32 BgmGetResumeWaitChan_207e90(void);
extern s32 GetStreamMgr_207ea0(void);

extern s16 D_00481C84;
extern s16 D_00481C88;
extern u8 D_00481C8C;

void StreamStep_206f20(void) {
    f32 temp_f20;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;

    temp_f20 = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    temp_2 = GetStreamMgr_207ea0();
    StreamMgrUpdate_1d6940(temp_2, temp_f20);
    if ((D_00481C84 != D_00481C88) && (StreamMgrChanIsFading_1d6360(temp_2, 0) == 0)) {
        BgmPlayTrackIfChangedMaybe_207880(D_00481C88, D_00481C8C);
    }
    temp_2_2 = StreamMgrGetChan_1d6900(temp_2, BgmGetResumeWaitChan_207e90());
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
