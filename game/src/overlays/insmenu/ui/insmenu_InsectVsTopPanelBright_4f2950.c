/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTopPanelBright_4f2950 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F2950 -- the insmenu_FUN_004EEF10 pair with a THIRD call: the
 * same colour written to two widget ids. */
extern u8 insmenu_D_004FA180[];
/*rgp*/
/*rgp*/
void insmenu_InsectVsTopPanelBright_4f2950(void)
{
    UiSetWidgetColor_2905b0(insmenu_D_004FA180, 1, 1.0f, 1.0f, 1.0f, 1.0f);
    UiSetWidgetTextColor_2907d0(insmenu_D_004FA180, 0x37, 0xFF303030, 1);
    UiSetWidgetTextColor_2907d0(insmenu_D_004FA180, 0x38, 0xFF303030, 1);
}
