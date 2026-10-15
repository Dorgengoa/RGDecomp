#include "types.h"

extern void CharaEffEntryInit_230760(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x54];
    s32 m54;
    s32 m58;
};

void CharaEffEntryInitNamed_230710(struct Obj0 *p0, s32 p1, s32 p2)
{
    CharaEffEntryInit_230760(p0);
    p0->m54 = p1;
    p0->m58 = p2;
}
