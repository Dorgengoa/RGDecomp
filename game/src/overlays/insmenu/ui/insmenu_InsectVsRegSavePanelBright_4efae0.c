/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegSavePanelBright_4efae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EFAE0 -- two calls; the first passes the SAME 1.0f four
 * times.  mwcc materialises the constant once into $f12 and copies
 * it out with three `mov.s`, which is exactly retail's shape -- do
 * not read the mov.s run as four separate values. */
extern u8 insmenu_D_004FA180[];
/*rgp*/
/*rgp*/
void insmenu_InsectVsRegSavePanelBright_4efae0(void)
{
    UiSetWidgetColor_2905b0(insmenu_D_004FA180, 0x19, 1.0f, 1.0f, 1.0f, 1.0f);
    UiSetWidgetTextColor_2907d0(insmenu_D_004FA180, 0x27, 0xFF303030, 1);
}
