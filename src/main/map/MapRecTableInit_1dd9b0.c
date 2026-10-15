#include "types.h"

extern void Nop_1ed0b0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 m00;
    u8 pad001[0x23];
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 m30;
    s16 m34;
    s16 m36;
    s16 m38;
    s16 m3A;
    s16 m3C;
    s16 m3E;
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
};

void MapRecTableInit_1dd9b0(struct Obj0 *p0)
{
    Nop_1ed0b0();
    p0->m00 = 0;
    p0->m24 = 0;
    p0->m28 = 0;
    p0->m2C = 0;
    p0->m34 = -1;
    p0->m36 = -1;
    p0->m30 = 0;
    p0->m40 = 0;
    p0->m38 = 0;
    p0->m44 = 0;
    p0->m3A = 0;
    p0->m48 = 0;
    p0->m3C = 0;
    p0->m4C = 0;
    p0->m3E = 0;
}
