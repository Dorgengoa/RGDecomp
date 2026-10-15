#include "types.h"

extern void ListIterReset_257ad0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
    s32 m18;
};

void EventGlobalObjSubReset_257a50(struct Obj0 *p0)
{
    ListIterReset_257ad0((struct Obj0 *)((u8 *)p0 + 4));
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
}
