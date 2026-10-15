#include "types.h"

extern s16 GameSceneGetBgmTrack_1d1170(s32 arg0);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern void *GetGameData_1fede0(void);
extern void BgmRequestTrack_2077e0(s16 arg0, s32 arg1);
extern s32 BgmGetResumeWaitChan_207e90(void);
extern s16 *PartyGetBgmOverride_3cb100(s32 arg0);

void BgmUpdateStep_207050(void) {
    s16 *temp_2;

    if (BgmGetResumeWaitChan_207e90() == -1) {
        if (GetGameMode_1f59c0() != 0xF && GetGameMode_1f59c0() != 0x10) {
            temp_2 = PartyGetBgmOverride_3cb100(*(s32 *)((u8 *)GetGameData_1fede0() + 0x18));
            if (temp_2 != NULL) {
                BgmRequestTrack_2077e0(*temp_2, 1);
                return;
            }
        }
        BgmRequestTrack_2077e0(GameSceneGetBgmTrack_1d1170(GetCurrentScene_1f5be0()), 1);
    }
}
