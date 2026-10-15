#include "types.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz154540 asm("vf0");
extern u128 va154540 asm("vf1");
extern u128 vb154540 asm("vf2");

typedef struct Res {
    s32 hasA;
    s32 hasB;
    u8 pad8[8];
    f32 a;
    u8 pad14[0xC];
    u128 b;
} Res;

typedef struct Node {
    u8 pad0[6];
    u8 dirty;
    u8 pad7[0x19];
    u128 v20;
} Node;

void AnimSlotApplyToMaterial_154540(Res *r, Node *n)
{
    n->dirty = 1;
    if (r->hasA != 0) {
        *(f32 *)((u8 *)n + 0x2C) = r->a;
    }
    if (r->hasB != 0) {
        va154540 = *(volatile u128 *)&n->v20;
        vb154540 = *(volatile u128 *)&r->b;
        va154540 = _vaddbc(va154540, 0xE, vb154540, vz154540, 8);
        n->v20 = va154540;
    }
}
