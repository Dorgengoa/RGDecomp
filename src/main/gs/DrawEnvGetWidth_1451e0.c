#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x270];
    struct Obj1 *m270;
};

struct Obj1 {
    u8 pad000[0x4];
    s32 m04;
};

s32 DrawEnvGetWidth_1451e0(struct Obj0 *p0)
{
    return p0->m270->m04;
}
