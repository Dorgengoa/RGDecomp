/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsBackGuideInit_4ea060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EA060 (100 bytes, 22 instructions, 4 calls) -- show one widget
 * and give it its label.  `daddu $7, $6, $0` in the first call's delay slot is
 * mwcc sharing the 1 it already materialised for the third argument; both are
 * written out as literals.
 */

extern u8 insmenu_D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsBackGuideInit_4ea060(void)
{
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x59, 1, 1);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x59, 0.0f);
    UiSetTextString_28f510(insmenu_D_004FA180, 0x5B, MsgTableLookup_28aa30(D_004842FC, 0x5E0), 0);
}
