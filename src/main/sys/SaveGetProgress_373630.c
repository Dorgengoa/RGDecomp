#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x520];
    s32 m520;
    s32 m524;
};

struct Obj1 {
    s32 m00;
};

s32 SaveGetProgress_373630(struct Obj0 *p0, struct Obj1 *p1)
{
    if (p1 != 0) {
        p1->m00 = p0->m520;
    }
    return p0->m524;
}
