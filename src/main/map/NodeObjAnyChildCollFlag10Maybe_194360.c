#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x94];
    s32 m94;
};

struct Obj1 {
    s32 m00;
    u8 pad004[0xC];
    struct Obj2 *m10;
};

struct Obj2 {
    u8 pad000[0x78];
    s32 m78;
};

s32 NodeObjAnyChildCollFlag10Maybe_194360(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 *l0;
    struct Obj2 * t1;
    s32 t2;
    s32 t3;

    t0 = p0->m94;
    l0 = (struct Obj1 *)t0;
    while (l0 != 0) {
        t1 = l0->m10;
        t2 = l0->m10->m78;
        if ((t2 & 0x10) != 0) {
            return 1;
        }
        t3 = l0->m00;
        l0 = (struct Obj1 *)t3;
    }
    return 0;
}
