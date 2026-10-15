#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    u8 m08;
    u8 pad009[0x1F];
    u8 m28;
    u8 pad029[0x1F];
    u8 m48;
    u8 pad049[0x1F];
    s32 m68;
    s32 m6C;
};

struct Obj0 *CBlurTexCtor_179330(struct Obj0 *p0)
{
    p0->m08 = 0;
    p0->m28 = 0;
    p0->m48 = 0;
    p0->m68 = 0;
    p0->m00 = 1;
    p0->m6C = 0;
    return p0;
}
