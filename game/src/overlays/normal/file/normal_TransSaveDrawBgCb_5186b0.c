/* rgp:protos */
#define RGP_SELF_normal_TransSaveDrawBgCb_5186b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005186B0 -- twin of 0x00518660: same five-parameter EABI shape and
 * the same NULL guard, but the gp handle is PASSED to func_290770 rather than
 * only tested, and the shared exit is 0. */

extern void *D_00484710;   /* gp - 0xA60 */

/*rgp*/
/*rgp*/

s32 normal_TransSaveDrawBgCb_5186b0(void *a, s32 b, s32 c, s32 d, s32 e)
{
    if (e != 0) {
        if (D_00484710 != NULL) {
            SaveScreenBgScrollDraw_3768d0(a, UiGetWidgetAlpha_290770(D_00484710, 0x7531));
        }
    }
    return 0;
}
