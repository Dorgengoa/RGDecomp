/* rgp:protos */
#define RGP_SELF_ShopRowGetBasePrice_3ce7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483910;

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 ShopRowGetBasePrice_3ce7f0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv4;
    s32 t1;
    s32 rv3;
    s32 r0;
    s32 rv2;
    s32 t2;
    s32 r1;

    t0 = p0->m00;
    rv4 = rv3;
    if (t0 == 0) {
        rv4 = -1;
    } else {
        t1 = D_00483910;
        rv3 = rv2;
        if (t1 == 0) {
            rv3 = -1;
        } else {
            r0 = ShopRowIsUnavailable_3ce6b0(p0);
            rv2 = r1;
            if (r0 != 0) {
                rv2 = -1;
            } else {
                t2 = p0->m00;
                r1 = ((short)ItemGetBuyPrice_3d4340(t2));
                rv2 = r1;
            }
            rv3 = rv2;
        }
        rv4 = rv3;
    }
    return rv4;
}
