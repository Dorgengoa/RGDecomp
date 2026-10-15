#include "types.h"

extern void TargetRefClear_2e71d0(void *);
extern void XformInitIdentity_2e7970(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x108];
    s32 m108;
    s32 m10C;
    s32 m110;
    s16 m114;
    u8 m116;
};

void EvTargetSetReset_336bb0(struct Obj0 *p0)
{
    p0->m114 = -1;
    TargetRefClear_2e71d0(p0);
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0x30));
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0x60));
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0x90));
    XformInitIdentity_2e7970((struct Obj0 *)((u8 *)p0 + 0xC0));
    p0->m108 = 0;
    p0->m10C = 0;
    p0->m110 = 0;
    p0->m116 = 0;
}
