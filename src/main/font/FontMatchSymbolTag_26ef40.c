#include "types.h"

extern void * TextSymbolTagFind_26efe0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
    u16 m06;
};

struct Obj1 {
    s16 m00;
};

struct Obj2 {
    s32 m00;
};

s32 FontMatchSymbolTag_26ef40(s32 p0, struct Obj1 *p1, struct Obj2 *p2)
{
    struct Obj0 *r0;
    u16 t0;
    s16 t1;

    r0 = TextSymbolTagFind_26efe0(p0);
    if (r0 != 0) {
        t0 = r0->m06;
        p1->m00 = t0;
        t1 = r0->m04;
        p2->m00 = t1;
        return 1;
    }
    return 0;
}
