#include "types.h"

extern void strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

extern u8 D_0045EDA0[];

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u128 m10;
    s32 m20;
    s32 m24;
    s32 m28;
    u8 pad02C[0x20];
    s32 m4C;
};

void EventSubNodeReset_2520d0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m10 = 0;
    p0->m20 = 0;
    p0->m24 = 0;
    p0->m28 = 0;
    strcpy((struct Obj0 *)((u8 *)p0 + 0x2C), D_0045EDA0);
    p0->m4C = 0;
}
