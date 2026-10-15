#include "types.h"

extern s32 AudioDecPause_1d3140(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x28];
    s32 m2C;
    u8 pad030[0x4];
    s32 m34;
    s32 m38;
    u8 pad03C[0x4];
    s32 m40;
    u8 pad044[0x8];
    s32 m4C;
    s32 m50;
    s32 m54;
};

s32 AudioDecReset_1d3070(struct Obj0 *p0)
{
    s32 r0;

    r0 = AudioDecPause_1d3140(p0);
    p0->m00 = 0;
    p0->m2C = 0;
    p0->m34 = 0;
    p0->m38 = 0;
    p0->m40 = 0;
    p0->m54 = 0;
    p0->m4C = 0;
    p0->m50 = 0;
    return 0;
}
