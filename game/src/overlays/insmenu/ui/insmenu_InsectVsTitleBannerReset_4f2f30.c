/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTitleBannerReset_4f2f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F2F30 (92 bytes, 23 instructions, 3 calls) -- show one widget,
 * clear its fade and nudge it up by 0x3C.  `daddu $7, $6, $0` is mwcc sharing
 * the 1 it materialised for the third argument.
 */

extern u8 insmenu_D_004FA180[];

/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsTitleBannerReset_4f2f30(void)
{
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x39, 1, 1);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x39, 1.0f);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x39, 0, -0x3C);
}
