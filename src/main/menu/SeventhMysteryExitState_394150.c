#include "types.h"

extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void *GetLoaderMgr_1f59d0(void);
extern void StreamSetChanVolumeFade_1cd960(void *, s32, s32, f32);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern u8 D_004E9550[];
extern s32 D_00483470;
extern f32 D_0047D7C8;

s32 SeventhMysteryExitState_394150(s32 a, s32 b)
{
    void *r;

    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_004E9550, 0xA, 0.0f, D_0047D7C8, -1.0f);
        r = GetLoaderMgr_1f59d0();
        StreamSetChanVolumeFade_1cd960(r, 0, 0xF, 1.0f);
    }
    StateMachineSetState_28ede0(&D_00483470, 0x7533, 0);
    return 1;
}
