/* rgp:protos */
#define RGP_SELF_BgmUpdateStep_207050 1
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

void BgmUpdateStep_207050(void) {
    s16 *temp_2;

    if (((short)BgmGetResumeWaitChan_207e90()) == -1) {
        if (GetGameMode_1f59c0() != 0xF && GetGameMode_1f59c0() != 0x10) {
            temp_2 = ((s16 *)PartyGetBgmOverride_3cb100(*(s32 *)((u8 *)GetGameData_1fede0() + 0x18)));
            if (temp_2 != NULL) {
                BgmRequestTrack_2077e0(*temp_2, 1);
                return;
            }
        }
        BgmRequestTrack_2077e0(GameSceneGetBgmTrack_1d1170(GetCurrentScene_1f5be0()), 1);
    }
}
