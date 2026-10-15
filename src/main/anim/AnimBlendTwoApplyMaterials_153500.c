#include "types.h"
/* AnimBlendTwoApplyMaterials_153500 -- asm-free (s88m): the vu0inline.h CopyXYZ helper is spelled with
 * mwcc VU0 intrinsics on file-scope vf0/vf1/vf2 register bindings.
 * - optimization_level 3 + the double (s32) round trip on s keep &r->b in a GPR
 *   (retail `addiu v0,sp,K; lqc2 vf2,0(v0)`), opt_loop_invariants off stops it being
 *   hoisted into a callee-saved reg; always_inline keeps the nested inlines.
 * - `one = (f32)one;` keeps 1.0f in its own FPR (f20) once LICM is off.
 * - bindings are `extern` so no .bss objects are emitted (insect_InsectPieceFaceCell_515590 idiom). */
#pragma optimization_level 3
#pragma opt_loop_invariants off
#pragma always_inline on

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz153500 asm("vf0");
extern u128 va153500 asm("vf1");
extern u128 vb153500 asm("vf2");


static inline void CopyXYZ(void *d, void *s)
{
    u128 *pd = (u128 *)(u32)d;
    u128 *ps = (u128 *)(s32)(u32)s;
    ps = (u128 *)(s32)ps;
    va153500 = *pd;
    vb153500 = *ps;
    va153500 = _vaddbc(va153500, 0xE, vb153500, vz153500, 8);
    *pd = va153500;
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
extern Key *AnimResGetFrameKeyList_14bf10(s32);
extern Node *ArrayGetChecked_153160(void *, u16);
extern void AnimKeyEvalMaterial_155af0(Res *, Key *, f32);
extern void AnimKeyBlendMaterial_1559e0(Res *, Key *, f32, f32);

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

static inline s32 ApplyAll(void *o, s32 id, f32 t)
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

static inline s32 Less(Key *a, Key *b)
{
    return a != 0 && a->id < b->id;
}

static inline s32 Less2(Key *a, Key *b)
{
    if (a == 0) {
        return 0;
    }
    return a->id < b->id;
}

s32 AnimBlendTwoApplyMaterials_153500(void *o, s32 idA, s32 idB, f32 tA, f32 tB, f32 w)
{
    Res ra;
    Res rb;
    Res rab;
    Key *ka;
    Key *kb;
    Node *n;
    f32 one;

    if (o == 0) {
        return 0;
    }
    ka = AnimResGetFrameKeyList_14bf10(idA);
    kb = AnimResGetFrameKeyList_14bf10(idB);
    if (ka == 0 && kb == 0) {
        return 0;
    }
    if (ka == 0) {
        return ApplyAll(o, idB, tB);
    }
    if (kb == 0) {
        return ApplyAll(o, idA, tA);
    }
    rab.hasB = 0;
    one = 1.0f;
    one = (f32)one;
    rab.hasA = 0;
    while (ka != 0 || kb != 0) {
        if (ka != 0 && kb == 0) {
            n = ArrayGetChecked_153160(o, ka->id);
            AnimKeyEvalMaterial_155af0(&ra, ka, tA);
            if (n != 0) {
                Apply(n, &ra);
            }
            ka = ka->next;
        } else if (ka == 0 && kb != 0) {
            n = ArrayGetChecked_153160(o, kb->id);
            AnimKeyEvalMaterial_155af0(&rb, kb, tB);
            if (n != 0) {
                Apply(n, &rb);
            }
            kb = kb->next;
        } else {
            while (!!kb && ka->id > kb->id) {
                n = ArrayGetChecked_153160(o, kb->id);
                AnimKeyEvalMaterial_155af0(&rb, kb, tB);
                if (n != 0) {
                    Apply(n, &rb);
                }
                kb = kb->next;
            }
            if (kb == 0) {
                continue;
            }
            while (!!ka && ka->id < kb->id) {
                n = ArrayGetChecked_153160(o, ka->id);
                AnimKeyEvalMaterial_155af0(&ra, ka, tA);
                if (n != 0) {
                    Apply(n, &ra);
                }
                ka = ka->next;
            }
            if (ka == 0) {
                continue;
            }
            if (ka->id == kb->id) {
                n = ArrayGetChecked_153160(o, ka->id);
                rab.hasB = 0;
                rab.hasA = 0;
                AnimKeyBlendMaterial_1559e0(&rab, ka, tA, one - w);
                AnimKeyBlendMaterial_1559e0(&rab, kb, tB, w);
                if (n != 0) {
                    Apply(n, &rab);
                }
            }
            ka = ka->next;
            kb = kb->next;
        }
    }
    return 1;
}
