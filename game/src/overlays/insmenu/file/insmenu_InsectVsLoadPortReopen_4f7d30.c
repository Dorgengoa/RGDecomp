/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadPortReopen_4f7d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F7D30 (160 bytes) -- tear the insect menu down, but only once
 * the fade widget has run out.
 *
 * ★ `mtc1 $0, $f1` beside `c.le.s $f0, $f1` is the literal `0.0f`: mwcc builds
 * a zero float straight out of $0 rather than loading a constant.
 * ★ The teardown block is the FALL-THROUGH arm and `return 1` is the join, so
 * the guard is written in its positive form and the whole body sits inside it. */

extern u8 insmenu_D_004FA180[];
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadPortReopen_4f7d30(void)
{
    if (UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x9CA7) <= 0.0f) {
        insmenu_InsectVsLoadPanelLayout_4f7dd0();
        insmenu_InsectVsSavePortSelectDraw_4f6bf0(-1);
        insmenu_InsectVsSaveHighlightOption_4f6bb0(-1);
        insmenu_InsectVsSaveListRefresh_4ebc30(0, 0);
        SaveUiScrollBarLayoutMaybe_377830(0x890C, 0x15B, 3, 0x32, 0);
        insmenu_InsectVsLoadWidgetsFade_4f6ac0(0);
        insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
        StateMachineSetState_28ede0(&D_004842E8, 0x88BA, 0);
    }
    return 1;
}
