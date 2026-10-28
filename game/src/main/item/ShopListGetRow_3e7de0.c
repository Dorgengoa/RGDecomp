/* rgp:protos */
#define RGP_SELF_ShopListGetRow_3e7de0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x8];
    struct Obj1 *m08;
};

struct Obj1 {
    u8 pad000[0xA8];
    s32 mA8;
};

s32 ShopListGetRow_3e7de0(struct Obj0 *p0, s32 p1)
{
    struct Obj1 * t0;
    s32 t1;
    s32 r0;

    t0 = p0->m08;
    if (t0 != 0) {
        t1 = p0->m08->mA8;
        r0 = ShopRowGet_4244b0(t1, p1);
        return r0;
    }
    return 0;
}
