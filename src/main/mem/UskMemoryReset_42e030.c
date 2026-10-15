#include "types.h"

extern void UskStackClear_42e460(void *);
extern void DListClear_42ea80(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

void UskMemoryReset_42e030(struct Obj0 *p0)
{
    p0->m10 = 0;
    UskStackClear_42e460((struct Obj0 *)((u8 *)p0 + 0x14));
    DListClear_42ea80(p0);
}
