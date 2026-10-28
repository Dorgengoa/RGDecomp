/* rgp:protos */
#define RGP_SELF_normal_ShopMenuTopCursorBobCb_5097b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005097B0 -- forwards its two arguments to 0x005097E0 with the two
 * trailing integers zeroed. */
/*rgp*/

s32 normal_ShopMenuTopCursorBobCb_5097b0(void *o, void *w)
{
    normal_ShopMenuCursorBob_5097e0(o, w, 0, 0);
    return 1;
}
