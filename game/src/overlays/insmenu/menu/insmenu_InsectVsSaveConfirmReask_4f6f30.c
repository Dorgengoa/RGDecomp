/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveConfirmReask_4f6f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F6F30 (120 bytes) -- start the item list's fade when asked to,
 * then raise the "list settled" event once the fade has run out. */

extern u8 insmenu_D_004FA180[];
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern s16 D_00484364;          /* gp - 0xE0C */
extern f32 D_0047D3C8;          /* gp - 0x7DA8 */

/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsSaveConfirmReask_4f6f30(s32 a, s32 start)
{
    if (start) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x5F, 0.0f, D_0047D3C8, -1.0f);
        D_00484364 = 1;
    }
    if (UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x5F) <= 0.0f) {
        StateMachineSetState_28ede0(&D_004842E8, 0x88CC, 0);
    }
    return 1;
}
