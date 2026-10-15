#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    s32 m04;
};

struct Obj1 {
    s32 m00;
    s32 m04;
};

struct Obj1 *TextReaderValueCopy_15f6a0(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m00 = p1->m00;
    p0->m04 = p1->m04;
    return p0;
}
