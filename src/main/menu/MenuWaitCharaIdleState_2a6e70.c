#include "types.h"

struct RFUN_002a6e70 { u8 pad000[0x8]; void *f08; };

extern void *D_00482364 __attribute__((section(".sdata")));
extern void *D_0048235C __attribute__((section(".sdata")));
extern const u8 D_004DB430[];

extern void UiEntryListSelectByTag_28ea90(void *a, s32 b, s32 c);
extern struct RFUN_002a6e70 *GetGameData_1fede0(void);
extern s32 WorldDataMgrNoRequestPending_3eef10(void *a);
extern void StateMachineSetState_28ede0(void *a, s32 b, s32 c);
extern void UiSelFrameAnimStep_28d820(const u8 *a, s32 b);

s32 MenuWaitCharaIdleState_2a6e70(s32 a, s32 b)
{
    if (b != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
    }
    if (WorldDataMgrNoRequestPending_3eef10(GetGameData_1fede0()->f08) != 0) {
        StateMachineSetState_28ede0(D_0048235C, 0x3D, 0);
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
