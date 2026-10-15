#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    struct Obj1 *m10;
};

struct Obj1 {
    u8 pad000[0x2];
    s8 m02;
};

u8 ItemRecKindIs19_3d4610(struct Obj0 *p0)
{
    return (p0->m10->m02 == 0x13);
}
