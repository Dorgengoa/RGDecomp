#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x2C];
    struct Obj1 *m2C;
};

struct Obj1 {
    u8 pad000[0x50];
    s32 m50;
};

void ScreenFadeBlockSetCaptureObj_177f70(struct Obj0 *p0, struct Obj1 *p1, s32 p2)
{
    if (p1 != 0) {
        p0->m2C = p1;
        p1->m50 = p2;
    }
}
