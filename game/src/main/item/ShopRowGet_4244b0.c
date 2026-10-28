/* rgp:protos */
#define RGP_SELF_ShopRowGet_4244b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
    u8 pad012[0x2];
    s32 m14;
};

s32 ShopRowGet_4244b0(struct Obj0 *p0, s32 p1)
{
    s16 t0;
    s32 t1;

    if (p1 >= 0) {
        t0 = p0->m10;
        if (p1 < t0) goto ok;
    }
    return 0;
ok:
    t1 = p0->m14;
    if (t1 != 0) {
        return (t1 + p1 * 12);
    }
    return 0;
}
