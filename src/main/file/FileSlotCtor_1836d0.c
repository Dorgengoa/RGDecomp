#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 m00;
    u8 m01;
    u8 m02;
    u8 m03;
    u8 pad004[0x68];
    s32 m6C;
    s32 m70;
    u8 pad074[0x4];
    u8 m78;
};

struct Obj0 *FileSlotCtor_1836d0(struct Obj0 *p0)
{
    p0->m03 = 0;
    p0->m02 = 0;
    p0->m01 = 0;
    p0->m00 = 0;
    p0->m6C = 0;
    p0->m70 = 1;
    p0->m78 = 0;
    return p0;
}
