#include "types.h"

extern s32 ShopRowIsUnavailable_3ce6b0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004801F0;

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
    u8 pad000[0xC];
    s32 m0C;
};

s32 ShopRowGetItemName_3ce930(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 rv2;
    s32 r0;
    s32 rv1;
    s32 t1;
    struct Obj1 * t2;
    struct Obj2 * t3;
    s32 t4;

    t0 = p0->m00;
    rv2 = rv1;
    if (t0 == 0) {
        rv2 = 0;
    } else {
        r0 = ShopRowIsUnavailable_3ce6b0(p0);
        rv1 = t4;
        if (r0 != 0) {
            t1 = D_004801F0;
            rv1 = t1;
        } else {
            t2 = p0->m00;
            t3 = p0->m00->m10;
            t4 = p0->m00->m10->m0C;
            rv1 = t4;
        }
        rv2 = rv1;
    }
    return rv2;
}
