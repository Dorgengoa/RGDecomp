#include "types.h"

extern void DListInit_42eae0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x30];
    s32 m30;
    s32 m34;
    s32 m38;
    s32 m3C;
};

void ActionMgrReset_234860(struct Obj0 *p0)
{
    DListInit_42eae0(p0);
    DListInit_42eae0((struct Obj0 *)((u8 *)p0 + 0x10));
    DListInit_42eae0((struct Obj0 *)((u8 *)p0 + 0x20));
    p0->m30 = 0;
    p0->m34 = 0;
    p0->m3C = 0;
    p0->m38 = 0;
}
