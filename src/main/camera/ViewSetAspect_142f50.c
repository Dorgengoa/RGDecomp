#include "types.h"

extern void ViewSetProjection_143000(void *, f32, f32, f32, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xF20];
    struct Obj1 *mF20;
};

struct Obj1 {
    u8 pad000[0x14];
    f32 m14;
    u8 pad018[0x8];
    f32 m20;
    f32 m24;
    u8 pad028[0x20];
    f32 m48;
    f32 m4C;
};

void ViewSetAspect_142f50(struct Obj0 *p0, f32 fa0)
{
    if (p0->mF20 != 0) {
        ViewSetProjection_143000(p0, p0->mF20->m14, p0->mF20->m20, p0->mF20->m24, fa0, p0->mF20->m48, p0->mF20->m4C);
    }
}
