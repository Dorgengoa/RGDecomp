#include "types.h"

extern s32 NodeXformReset_186490(void *);
extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x3C];
    s32 m3C;
    s32 m40;
    s32 m44;
    u8 pad048[0x8];
    s32 m50;
    s32 m54;
    s32 m58;
    s32 m5C;
};

void FuncDataRecReset_192210(struct Obj0 *p0)
{
    s32 r0;

    r0 = NodeXformReset_186490(p0);
    p0->m3C = 0;
    p0->m40 = 0;
    p0->m44 = 1;
    p0->m50 = 0;
    p0->m54 = 0;
    p0->m5C = 0;
    p0->m58 = 0;
    memset((struct Obj0 *)((u8 *)p0 + 0x60), 0, 0x50);
}
