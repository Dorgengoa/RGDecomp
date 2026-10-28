/* rgp:protos */
#define RGP_SELF_ShopRowGetIcon_3ce8e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    struct Obj1 *m00;
};

struct Obj1 {
    u8 pad000[0x10];
    s32 m10;
};

s32 ShopRowGetIcon_3ce8e0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 rv3;
    s32 r0;
    s32 rv2;
    struct Obj1 * t1;
    s32 t2;
    s32 r1;

    t0 = p0->m00;
    rv3 = rv2;
    if (t0 == 0) {
        rv3 = 6;
    } else {
        r0 = ShopRowIsUnavailable_3ce6b0(p0);
        rv2 = r1;
        if (r0 != 0) {
            rv2 = 6;
        } else {
            t1 = p0->m00;
            t2 = p0->m00->m10;
            r1 = ItemDefGetIconIndex_40e1b0(t2);
            rv2 = r1;
        }
        rv3 = rv2;
    }
    return rv3;
}
