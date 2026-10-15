#include "types.h"

extern void NodeInit_185f60(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x6C];
    s32 m6C;
    s32 m70;
    s32 m74;
    s32 m78;
    s32 m7C;
    s32 m80;
    s32 m84;
    s32 m88;
    s32 m8C;
};

void NodeObjBasicInit_196880(struct Obj0 *p0)
{
    NodeInit_185f60(p0);
    p0->m6C = 0;
    p0->m70 = 0;
    p0->m78 = 0;
    p0->m74 = 0;
    p0->m7C = 0;
    p0->m80 = 0;
    p0->m8C = 0;
    p0->m88 = 0;
    p0->m84 = 0;
}
