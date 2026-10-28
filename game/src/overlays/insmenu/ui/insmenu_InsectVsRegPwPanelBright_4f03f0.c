/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegPwPanelBright_4f03f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F03F0 -- two calls; the first passes the SAME 1.0f four
 * times.  mwcc materialises the constant once into $f12 and copies
 * it out with three `mov.s`, which is exactly retail's shape -- do
 * not read the mov.s run as four separate values. */
extern u8 insmenu_D_004FA180[];
/*rgp*/
/*rgp*/
void insmenu_InsectVsRegPwPanelBright_4f03f0(void)
{
    UiSetWidgetColor_2905b0(insmenu_D_004FA180, 0x4C, 1.0f, 1.0f, 1.0f, 1.0f);
    UiSetWidgetTextColor_2907d0(insmenu_D_004FA180, 0x4E, 0xFF303030, 1);
}
