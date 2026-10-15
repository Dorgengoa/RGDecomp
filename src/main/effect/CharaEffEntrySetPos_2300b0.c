#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x30];
    f32 m30;
    f32 m34;
    f32 m38;
    u8 pad03C[0x24];
    u16 m60;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
};

void CharaEffEntrySetPos_2300b0(struct Obj0 *p0, struct Obj1 *p1)
{
    p0->m60 = (p0->m60 | 0x800);
    p0->m30 = p1->m00;
    p0->m34 = p1->m04;
    p0->m38 = p1->m08;
}
