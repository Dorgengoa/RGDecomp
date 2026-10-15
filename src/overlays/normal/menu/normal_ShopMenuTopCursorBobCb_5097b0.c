#include "types.h"
/* normal 0x005097B0 -- forwards its two arguments to 0x005097E0 with the two
 * trailing integers zeroed. */
extern s32 normal_ShopMenuCursorBob_5097e0(void *o, void *w, s32 c, s32 d);

s32 normal_ShopMenuTopCursorBobCb_5097b0(void *o, void *w)
{
    normal_ShopMenuCursorBob_5097e0(o, w, 0, 0);
    return 1;
}
