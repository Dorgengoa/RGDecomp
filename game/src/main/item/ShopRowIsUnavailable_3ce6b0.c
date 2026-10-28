/* rgp:protos */
#define RGP_SELF_ShopRowIsUnavailable_3ce6b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3CE6B0 { u8 pad000[0xA]; s16 f0A; };

s32 ShopRowIsUnavailable_3ce6b0(struct T3CE6B0 *p)
{
    s16 v;
    s32 r;

    v = p->f0A;
    r = 1;
    if (v == 1) goto zero;
    if (v != 2) goto out;
zero:
    r = 0;
out:
    return r;
}
