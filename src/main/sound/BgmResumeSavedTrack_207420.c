#include "types.h"

void Sprintf_1343b8(void *, void *, s16);
void StreamMgrSetChanVolumeFade_1d63a0(s32, s32, s32, f32);
void StreamMgrChanRestoreResumePoint_1d6480(s32, s32);
void StreamMgrPauseChan_1d6630(s32, s32);
void StreamMgrPlayChan_1d6670(s32, f32, s32);
void StreamMgrStopChan_1d66b0(s32, s32);
void StreamMgrStartChan_1d66f0(s32, s32, void *, s32);
s32 GetStreamMgr_207ea0(s16);
extern u8 D_0045C5C0[];
extern s16 D_00481C80;
extern s16 D_00481C84;
extern s16 D_00481C88;

void BgmResumeSavedTrack_207420(s32 arg0) {
    u8 sp30[0x80];
    s16 temp_4;
    s32 temp_2;

    if (D_00481C84 == D_00481C80) {
        StreamMgrSetChanVolumeFade_1d63a0(GetStreamMgr_207ea0(D_00481C80), 0, 0x3C, 1.0f);
        D_00481C80 = -1;
        D_00481C88 = D_00481C84;
        return;
    }
    if (D_00481C80 >= 0) {
        temp_2 = GetStreamMgr_207ea0(D_00481C80);
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
