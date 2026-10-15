#include "types.h"

typedef struct A {
    u8  pad000[0x4];
    s32 m04;
} A;

typedef struct B {
    u8  pad000[0xB4];
    u8 *mB4;
} B;

extern void VecAddScaled_13bdd0(void *d, void *s, f32 t);

void EffAttachIntegratePos_197a20(A *a, B *b, f32 t)
{
    u8 *p;

    p = b->mB4 + a->m04 * 16;
    VecAddScaled_13bdd0((u8 *)b + 0x10, p, t);
    VecAddScaled_13bdd0(p, p + 0x10, t);
}
