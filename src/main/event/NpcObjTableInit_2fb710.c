#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s16 m08;
    u8 pad00A[0x206];
    s32 m210;
    s32 m214;
    s16 m218;
    u8 pad21A[0x6];
    s16 m220;
    s16 m222;
    s16 m224;
};

void NpcObjTableInit_2fb710(struct Obj0 *p0)
{
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m210 = 0x442F0000;
    p0->m214 = 0x43FA0000;
    p0->m218 = 0;
    p0->m220 = 0;
    p0->m222 = 0;
    p0->m224 = -1;
}
