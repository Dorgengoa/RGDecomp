/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamViewClose_4f8990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F8990 (112 bytes) -- once the fade widget has run out, raise
 * either the "resumed" or the "opened" event.
 *
 * ★ `sb $0, -0xE18($28)` rides the call's delay slot: the flag is cleared in
 * the SOURCE before the call, which is what gives mwcc something to sink. */

extern u8 insmenu_D_004FA180[];
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern u8 D_00484358;           /* gp - 0xE18 */

/*rgp*/
/*rgp*/

s32 insmenu_InsectVsTeamViewClose_4f8990(void)
{
    if (UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x9CA7) <= 0.0f) {
        if (D_00484358 != 0) {
            D_00484358 = 0;
            StateMachineSetState_28ede0(&D_004842E8, 0x88C6, 0);
        } else {
            StateMachineSetState_28ede0(&D_004842E8, 0x88BF, 0);
        }
    }
    return 1;
}
