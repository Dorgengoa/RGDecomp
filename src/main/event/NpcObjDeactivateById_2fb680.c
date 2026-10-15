#include "types.h"

extern void * NpcObjFindById_2fb420(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xCC];
    s16 mCC;
};

struct Obj1 {
    u8 pad000[0x224];
    s16 m224;
};

struct Obj0 *NpcObjDeactivateById_2fb680(struct Obj1 *p0, s32 p1)
{
    struct Obj0 *r0;

    r0 = NpcObjFindById_2fb420(p0, p1);
    if (r0 != 0) {
        r0->mCC = 0;
        p0->m224 = -1;
    }
    return r0;
}
