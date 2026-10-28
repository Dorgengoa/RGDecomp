/* rgp:protos */
#define RGP_SELF_TransMenuItemPartyWaitState_37c900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct RFUN_0037c900 { u8 pad000[0x8]; void *f08; };

extern void *D_00484720 __attribute__((section(".sdata")));
extern void *D_0048470C __attribute__((section(".sdata")));
extern u8 D_004E9230[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TransMenuItemPartyWaitState_37c900(s32 a, s32 b)
{
    if (b != 0) {
        UiEntryListSelectByTag_28ea90(D_00484720, 0xF, 0);
    }
    if (WorldDataMgrNoRequestPending_3eef10(((struct RFUN_0037c900 *)GetGameData_1fede0())->f08) != 0) {
        StateMachineSetState_28ede0(D_0048470C, 0x34, 0);
    }
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
