/* rgp:protos */
#define RGP_SELF_MenuLeaderChangeDoneState_2b4d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void *D_00482360;
extern void *D_0048235C;

s32 MenuLeaderChangeDoneState_2b4d50(void)
{
    UiSetWidgetColor_2905b0(D_00482360, 0x132, 1.0f, 1.0f, 1.0f, 1.0f);
    StateMachineSetState_28ede0(D_0048235C, 0x4B, 0);
    return 1;
}
