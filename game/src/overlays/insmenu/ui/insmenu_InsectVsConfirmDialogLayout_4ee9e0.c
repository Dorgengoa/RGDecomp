/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsConfirmDialogLayout_4ee9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EE9E0 (216 bytes, 54 instructions, 10 calls) -- lay out the
 * confirm prompt: place and show the frame, then fill the two-line label from
 * the string bank.  `daddu $7, $6, $0` in the second call's delay slot is mwcc
 * sharing the 1 it already materialised.
 */

extern u8 insmenu_D_004FA180[];
extern s32 D_00481BBC;      /* gp - 0x35B4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsConfirmDialogLayout_4ee9e0(void)
{
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 6, 0x60, 0xF0);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 6, 1, 1);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 6, 0.0f);
    UiSetSpriteU_28f930(insmenu_D_004FA180, 8, 0x7A, 0);
    UiSetSpriteU_28f930(insmenu_D_004FA180, 8, 0x46, 1);
    UiSetTextString_28f510(insmenu_D_004FA180, 8, MsgTableLookup_28aa30(D_00481BBC, 0x52), 1);
    UiSetTextString_28f510(insmenu_D_004FA180, 8, MsgTableLookup_28aa30(D_00481BBC, 0x53), 2);
    insmenu_InsectVsBackGuideHide_4ea000();
}
