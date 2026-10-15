#include "types.h"

extern void EvObjReset_2f9eb0(void *);
extern void EventRecReset_2e5840(void *);
extern void TargetRefClear_2e71d0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xF0];
    s32 mF0;
    u8 pad0F4[0x30];
    s32 m124;
    s32 m128;
    s32 m12C;
    s32 m130;
    s32 m134;
    u8 m138;
    u8 pad139[0xF];
    s16 m148;
    s16 m14A;
};

void EvNodeAttachObjReset_3535c0(struct Obj0 *p0)
{
    EvObjReset_2f9eb0(p0);
    EventRecReset_2e5840((struct Obj0 *)((u8 *)p0 + 0xE0));
    p0->mF0 = 0;
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0xF4));
    p0->m124 = 0;
    p0->m128 = 0;
    p0->m12C = 0;
    p0->m130 = 0;
    p0->m134 = 0;
    p0->m138 = 0;
    p0->m148 = 0;
    p0->m14A = 0;
}
