#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
#pragma opt_propagation off

extern void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);
extern void StreamSetChanVolume_1cd9b0(s32, s32, f32);
extern void StreamPauseChan_1cd9f0(s32, s32);
extern void StreamStopChan_1cda60(s32, s32);
extern f32 GameSceneGetTimeStep_1ceba0(s32);
extern void ScreenFadeOutColor_1cf730(s32, s32, f32, f32, f32);
extern void StreamMgrUpdate_1d6940(s32, f32);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 GetStreamMgr_207ea0(void);
extern void MesWinOwnerClose_24eab0(void *);
extern s32 D_0047E7E4;

void EventPlayerAbort_2498b0(void *arg0, s32 arg1)
{
    f32 temp_f20;
    f32 z;
    s32 temp_16;

    temp_f20 = GameSceneGetTimeStep_1ceba0(arg1);
    temp_16 = GetLoaderMgr_1f59d0();
    if (!(*(s32 *)((u8 *)arg0 + 0xA60) & 4)) {
        if (D_0047E7E4 != 0) {
            z = 0.0f;
            ScreenFadeOutColor_1cf730(arg1, 0xA, z, z, z);
        }
        *(s32 *)((u8 *)arg0 + 0x484) = 0xC;
    } else {
        *(s32 *)((u8 *)arg0 + 0x484) = 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0xA60) & 2) {
        StreamSetChanVolumeFade_1cd960(temp_16, 0, 0xA, 0.0f);
        StreamSetChanVolume_1cd9b0(temp_16, 1, 0);
        StreamSetChanVolume_1cd9b0(temp_16, 2, 0);
        StreamPauseChan_1cd9f0(temp_16, 1);
        StreamPauseChan_1cd9f0(temp_16, 2);
        StreamStopChan_1cda60(temp_16, 1);
        StreamStopChan_1cda60(temp_16, 2);
    } else {
        StreamSetChanVolume_1cd9b0(temp_16, 1, 0);
        StreamSetChanVolume_1cd9b0(temp_16, 2, 0);
        StreamPauseChan_1cd9f0(temp_16, 1);
        StreamPauseChan_1cd9f0(temp_16, 2);
        StreamStopChan_1cda60(temp_16, 1);
        StreamStopChan_1cda60(temp_16, 2);
    }
    StreamMgrUpdate_1d6940(GetStreamMgr_207ea0(), temp_f20);
    MesWinOwnerClose_24eab0((u8 *)arg0 + 0x420);
    *(s32 *)((u8 *)arg0 + 0xA60) = *(s32 *)((u8 *)arg0 + 0xA60) | 0x10;
}
