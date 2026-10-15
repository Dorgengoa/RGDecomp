#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x96C];
    struct Obj1 *m96C;
};

struct Obj1 {
    u8 pad000[0x10];
    struct Obj2 *m10;
};

struct Obj2 {
    s16 m00;
};

s32 MenuObjInsectGetDefId_386d70(struct Obj0 *p0)
{
    struct Obj1 * t0;
    struct Obj2 * t1;
    s16 t2;

    t0 = p0->m96C;
    if (t0 != 0) {
        t1 = p0->m96C->m10;
        t2 = p0->m96C->m10->m00;
        return t2;
    }
    return 0;
}
