/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTitleBannerIsStill_4f2ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F2EA0 -- `sltu $2, $0, $2 / xori $2, $2, 0x1` is a bool built
 * from an inequality and negated in ONE expression.  s32 return, not u8: a u8
 * return would add `andi $2, $2, 0xFF` retail does not have. */
extern u8 insmenu_D_004FA180[];
/*rgp*/
s32 insmenu_InsectVsTitleBannerIsStill_4f2ea0(void)
{
    return !(UiWidgetIsMoving_290d30(insmenu_D_004FA180, 0x39) != 0);
}
