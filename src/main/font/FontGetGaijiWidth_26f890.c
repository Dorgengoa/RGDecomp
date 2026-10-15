#include "types.h"

extern void * FontFindGaijiMetric_26f8c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x6];
    s16 m06;
};

s32 FontGetGaijiWidth_26f890(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s16 t0;

    r0 = FontFindGaijiMetric_26f8c0(p0, (p1 & 0xFFFF));
    if (r0 != 0) {
        t0 = r0->m06;
        return t0;
    }
    return 0;
}
