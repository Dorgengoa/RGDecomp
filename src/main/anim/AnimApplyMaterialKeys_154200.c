#include "types.h"
#pragma optimization_level 3
#pragma opt_loop_invariants off
#pragma always_inline on

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz154200 asm("vf0");
extern u128 va154200 asm("vf1");
extern u128 vb154200 asm("vf2");

static inline void CopyXYZ(void *d, void *s)
{
    u128 *pd = (u128 *)(u32)d;
    u128 *ps = (u128 *)(s32)(u32)s;
    ps = (u128 *)(s32)ps;
    va154200 = *pd;
    vb154200 = *ps;
    va154200 = _vaddbc(va154200, 0xE, vb154200, vz154200, 8);
    *pd = va154200;
}

typedef struct Key {
    struct Key *next;
    u16 id;
} Key;

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

extern Key *AnimResGetMaterialKeyList_14bef0(s32);
extern Node *ArrayGetChecked_153160(s32, u16);
extern void AnimKeyEvalMaterial_155af0(Res *, Key *, f32);

static inline void Apply(Node *n, Res *r)
{
    n->dirty = 1;
    if (r->hasA != 0) {
        *(f32 *)((u8 *)n + 0x2C) = r->a;
    }
    if (r->hasB != 0) {
        CopyXYZ(&n->v20, &r->b);
    }
}

s32 AnimApplyMaterialKeys_154200(s32 o, s32 id, f32 t)
{
    Key *k;
    Node *n;
    Res r;

    if (o == 0) {
        return 0;
    }
    for (k = AnimResGetMaterialKeyList_14bef0(id); k != 0; k = k->next) {
        n = ArrayGetChecked_153160(o, k->id);
        if (n != 0) {
            AnimKeyEvalMaterial_155af0(&r, k, t);
            Apply(n, &r);
        }
    }
    return 1;
}
