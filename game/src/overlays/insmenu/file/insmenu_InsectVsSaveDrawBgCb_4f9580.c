/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveDrawBgCb_4f9580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F9580 (68 bytes) -- if the fifth parameter is set, read one
 * widget's value and push it at the object the first parameter names.
 *
 * ★ The guard tests $8, which is argument FIVE: mwcc's PS2 target is EABI and
 * passes eight integer arguments in $4..$11.  Four of the five parameters are
 * never read, and only the count is recoverable from the object. */

extern u8 insmenu_D_004FA180[];

/*rgp*/
/*rgp*/

s32 insmenu_InsectVsSaveDrawBgCb_4f9580(void *obj, s32 b, s32 c, s32 d, s32 on)
{
    if (on) {
        SaveScreenBgScrollDraw_3768d0(obj, UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x88B9));
    }
    return 0;
}
