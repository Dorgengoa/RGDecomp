#include "types.h"

extern s32 ShopRowIsUnavailable_3ce6b0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
};

s16 ShopRowGetStock_3ce860(struct Obj0 *p0)
{
    s32 r0;
    s16 t0;

    r0 = ShopRowIsUnavailable_3ce6b0(p0);
    if (r0 != 0) {
        return 0;
    }
    t0 = p0->m08;
    return t0;
}
