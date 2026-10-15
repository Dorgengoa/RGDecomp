#include "types.h"

struct T1A85F0 { u8 pad000[0xC]; f32 fC; };

extern void VecMul_13bd40(struct T1A85F0 *, void *);

void EffParamApplyCol_1a85f0(u8 *a, struct T1A85F0 *b)
{
    f32 t;

    t = b->fC;
    VecMul_13bd40(b, a + 0x40);
    b->fC = t;
}
