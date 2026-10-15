#include "types.h"

extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    u8 pad004[0x4];
    s16 m08;
    u8 pad00A[0x2];
    s32 m0C;
    s32 m10;
};

void InsectBreedRecReset_3d2730(struct Obj0 *p0)
{
    memset(p0, 0, 0x14);
    p0->m00 = -1;
    p0->m02 = -1;
    p0->m08 = -1;
    p0->m0C = 0xBF800000;
    p0->m10 = 0xBF800000;
}
