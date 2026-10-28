/* rgp:protos */
#define RGP_SELF_ShopRowGetItemIconIdMaybe_3ce890 1
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
struct Obj2;

struct Obj0 {
    struct Obj1 *m00;
};

struct Obj1 {
    u8 pad000[0x10];
    struct Obj2 *m10;
};

struct Obj2 {
    u8 pad000[0x2C];
    s16 m2C;
};

s32 ShopRowGetItemIconIdMaybe_3ce890(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 rv2;
    s32 r0;
    s32 rv1;
    struct Obj1 * t1;
    struct Obj2 * t2;
    s16 t3;

    t0 = p0->m00;
    rv2 = rv1;
    if (t0 == 0) {
        rv2 = -1;
    } else {
        r0 = ShopRowIsUnavailable_3ce6b0(p0);
        rv1 = t3;
        if (r0 != 0) {
            rv1 = -1;
        } else {
            t1 = p0->m00;
            t2 = p0->m00->m10;
            t3 = p0->m00->m10->m2C;
            rv1 = t3;
        }
        rv2 = rv1;
    }
    return rv2;
}
