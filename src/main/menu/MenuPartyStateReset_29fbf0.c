#include "types.h"

extern void memset(void *, s32, s32);
extern s32 UiPageClearMemStack_289c50(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4C4];
    s32 m4C4;
    s32 m4C8;
    s32 m4CC;
};

s32 MenuPartyStateReset_29fbf0(struct Obj0 *p0)
{
    s32 r1;

    memset((struct Obj0 *)((u8 *)p0 + 0x5C), 0, 0x468);
    p0->m4C4 = 0;
    p0->m4C8 = 0;
    p0->m4CC = 0;
    r1 = UiPageClearMemStack_289c50(p0);
    return 1;
}
