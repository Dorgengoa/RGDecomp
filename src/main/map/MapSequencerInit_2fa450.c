#include "types.h"

extern void DListInit_42eae0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
    s32 m24;
};

void MapSequencerInit_2fa450(struct Obj0 *p0)
{
    DListInit_42eae0(p0);
    DListInit_42eae0((struct Obj0 *)((u8 *)p0 + 0x10));
    p0->m20 = 0;
    p0->m24 = 0;
}
