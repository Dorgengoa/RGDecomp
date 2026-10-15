#include "types.h"

extern s32 EventCastSetFloatStubMaybe_257d10(void *, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004BDDB0[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x20];
    f32 m20;
};

struct Obj1 {
    u8 pad000[0x60];
    s32 m60;
};

s32 EvSubNodeCastSetFloatStubMaybe_252510(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 r;

    r = EventCastSetFloatStubMaybe_257d10(D_004BDDB0, p1->m60, p0->m20);
    return 0;
}
