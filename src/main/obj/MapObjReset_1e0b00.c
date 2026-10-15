#include "types.h"

extern void LoadHandleReset_1ccc10(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
    s16 m14;
    s16 m16;
};

void MapObjReset_1e0b00(struct Obj0 *p0)
{
    LoadHandleReset_1ccc10(p0);
    p0->m0C = 0;
    p0->m10 = -1;
    p0->m14 = -1;
    p0->m16 = 0;
}
