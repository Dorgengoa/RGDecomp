/* rgp:protos */
#define RGP_SELF_normal_ShopMenuRowInfoShow_509460 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00509460 -- guard wrapper in front of 0x00509520: the handle is
 * dereferenced only when non-NULL, and is dropped again if either liveness
 * probe fires.  All five integer arguments plus $f12 are forwarded. */
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuRowInfoShow_509460(void **h, f32 x, s32 b, s32 c, s32 d, s32 e)
{
    void *p;

    p = NULL;
    if (h != NULL) {
        p = *h;
    }
    if (((unsigned char)ShopRowIsLocked_3ce690(h)) != 0 || ((unsigned char)ShopRowIsRestock_3ce6a0(h)) != 0) {
        p = NULL;
    }
    normal_ShopMenuItemInfoShow_509520(p, b, c, d, e, x);
    return 1;
}
