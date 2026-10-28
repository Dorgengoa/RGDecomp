/* rgp:protos */
#define RGP_SELF_MenuLeaderChangeFadeState_2b4ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void *D_00482360;
extern void *D_0048235C;
extern f32 D_0047D680;

s32 MenuLeaderChangeFadeState_2b4ee0(s32 a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x132, 0.0f, D_0047D680, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x68, 0);
    }
    return 1;
}
