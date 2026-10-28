/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSourceChoiceClose_4f8630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F8630 (224 bytes) -- start the sub-panel's fade when asked to,
 * then raise the event the current mode calls for once it has run out.
 *
 * ★ The mode == 0 arm is written as the `else` of a NEGATIVE outer guard, not
 * as the head of an if/else-if chain: retail tests 0 first and lays its block
 * LAST, which is what an inverted guard does and an ordinary chain does not.
 * Spelled `if (mode == 0) ... else if (mode == 2) ...` the arms come out in the
 * wrong order and the unit reads 24 bad at the right length. */

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern s16 D_0048436C;          /* gp - 0xE04 */
extern f32 D_0047D3C8;          /* gp - 0x7DA8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsSourceChoiceClose_4f8630(s32 a, s32 start)
{
    s16 mode;

    if (start) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x5C, 0.0f, D_0047D3C8, -1.0f);
        UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x5E, 0.0f);
    }
    if (UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x5C) <= 0.0f) {
        mode = D_0048436C;
        if (mode != 0) {
            if (mode == 2) {
                UiEntryListResetRectByTag_28eb10(insmenu_D_004FA1A0, 0x88B9);
                StateMachineSetState_28ede0(&D_004842E8, 0x88BE, 0);
            } else if (mode == 1) {
                StateMachineSetState_28ede0(&D_004842E8, 0x88C9, 0);
            }
        } else {
            StateMachineSetState_28ede0(&D_004842E8, 0x88BF, 0);
        }
    }
    return 1;
}
