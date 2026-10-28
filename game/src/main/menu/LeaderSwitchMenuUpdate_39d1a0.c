/* rgp:protos */
#define RGP_SELF_LeaderSwitchMenuUpdate_39d1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00483600;
extern s16 D_00483620;
extern u8 D_004E9610[];

void LeaderSwitchMenuUpdate_39d1a0(void)
{
    s32 v;

    v = D_00483620;
    if (v != 0) {
        v = (s16)v;
        if (v == 1) {
            D_00483620 = 2;
            StateMachineSetState_28ede0(&D_00483600, 0x7149, 1);
        }
        UiUpdateWidgets_2913a0(D_004E9610);
        StateMachineUpdate_28ed70(&D_00483600);
    }
}
