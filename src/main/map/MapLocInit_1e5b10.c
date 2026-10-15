#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
    s16 m08;
    u8 m0A;
    u8 m0B;
    u8 m0C;
    u8 pad00D[0x1F];
    s16 m2C;
    s16 m2E;
};

void MapLocInit_1e5b10(struct Obj0 *p0)
{
    p0->m00 = -1;
    p0->m02 = -1;
    p0->m04 = -1;
    p0->m06 = -1;
    p0->m08 = -1;
    p0->m0A = 0;
    p0->m0B = 0;
    p0->m0C = 0;
    p0->m2C = -1;
    p0->m2E = -1;
}
