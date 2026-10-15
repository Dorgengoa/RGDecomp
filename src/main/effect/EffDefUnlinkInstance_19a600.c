#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0xD8];
    struct Obj3 *mD8;
    struct Obj1 *mDC;
};

struct Obj1 {
    u8 pad000[0xD8];
    struct Obj3 *mD8;
};

struct Obj2 {
    u8 pad000[0x5C];
    struct Obj1 *m5C;
};

struct Obj3 {
    u8 pad000[0xDC];
    struct Obj1 *mDC;
};

void EffDefUnlinkInstance_19a600(struct Obj2 *p0, struct Obj0 *p1)
{
    if (p1->mD8 == 0) {
        if (p1->mDC != 0) {
            p1->mDC->mD8 = 0;
        }
        p0->m5C = p1->mDC;
    } else {
        p1->mD8->mDC = p1->mDC;
        if (p1->mDC != 0) {
            p1->mDC->mD8 = p1->mD8;
        }
    }
}
