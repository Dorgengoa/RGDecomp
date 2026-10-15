#include "types.h"
/* normal 0x00509460 -- guard wrapper in front of 0x00509520: the handle is
 * dereferenced only when non-NULL, and is dropped again if either liveness
 * probe fires.  All five integer arguments plus $f12 are forwarded. */
extern s32 func_3CE690(void *p);
extern s32 func_3CE6A0(void *p);
extern s32 normal_ShopMenuItemInfoShow_509520(void *p, s32 b, s32 c, s32 d, s32 e, f32 x);

s32 normal_ShopMenuRowInfoShow_509460(void **h, f32 x, s32 b, s32 c, s32 d, s32 e)
{
    void *p;

    p = NULL;
    if (h != NULL) {
        p = *h;
    }
    if (func_3CE690(h) != 0 || func_3CE6A0(h) != 0) {
        p = NULL;
    }
    normal_ShopMenuItemInfoShow_509520(p, b, c, d, e, x);
    return 1;
}
