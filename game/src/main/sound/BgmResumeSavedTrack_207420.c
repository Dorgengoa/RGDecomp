/* rgp:protos */
#define RGP_SELF_BgmResumeSavedTrack_207420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void Sprintf_1343b8(void *, void *, s16);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045C5C0[];
extern s16 D_00481C80;
extern s16 D_00481C84;
extern s16 D_00481C88;

void BgmResumeSavedTrack_207420(s32 arg0) {
    u8 sp30[0x80] __attribute__((aligned(16)));
    s16 temp_4;
    s32 temp_2;

    if (D_00481C84 == D_00481C80) {
        StreamMgrSetChanVolumeFade_1d63a0(((s32)GetStreamMgr_207ea0()), 0, 0x3C, 1.0f);
        D_00481C80 = -1;
        D_00481C88 = D_00481C84;
        return;
    }
    if (D_00481C80 >= 0) {
        temp_2 = ((s32)GetStreamMgr_207ea0());
        StreamMgrPauseChan_1d6630(temp_2, 0);
        StreamMgrStopChan_1d66b0(temp_2, 0);
        if (D_00481C80 > 0) {
            Sprintf_1343b8(&sp30, D_0045C5C0, D_00481C80);
            StreamMgrStartChan_1d66f0(temp_2, 0, &sp30, arg0 & 0xFF);
            StreamMgrChanRestoreResumePoint_1d6480(temp_2, 0);
            StreamMgrPlayChan_1d6670(temp_2, 0, 0);
            StreamMgrSetChanVolumeFade_1d63a0(temp_2, 0, 0x3C, 1.0f);
        }
        temp_4 = D_00481C80;
        D_00481C80 = -1;
        D_00481C84 = temp_4;
        D_00481C88 = temp_4;
    }
}
