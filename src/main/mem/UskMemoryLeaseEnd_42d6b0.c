#include "types.h"

extern s32 UskStackGetTop_42e3c0(void *);
extern void HeapBlockAllocAtStart_42ddf0(void *, s32, s32, s32);
extern void UskStackClear_42e460(void *);

/* The +0x10 is emitted TWICE, so the source has two named steps, not one
   +0x20 constant. */

struct Hdr;

struct Hdr {
    u8 b[0x10];
};

struct Obj;

struct Obj {
    u8 pad000[0x10];
    s32 m10;
    u8 m14[0x2C];
    s32 m40;
};

s32 UskMemoryLeaseEnd_42d6b0(struct Obj *p)
{
    struct Hdr *h;
    s32 end;
    s32 n;

    if ((p->m40 & 2) == 0) {
        return 0;
    }
    h = (struct Hdr *)(p->m10 + 0x10);
    end = (s32)(h + 1);
    n = UskStackGetTop_42e3c0(p->m14) - end;
    HeapBlockAllocAtStart_42ddf0(p, p->m10, n, 0);
    p->m10 = 0;
    UskStackClear_42e460(p->m14);
    p->m40 = p->m40 & ~2;
    return n;
}
