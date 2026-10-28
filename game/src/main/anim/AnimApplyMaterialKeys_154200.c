/* rgp:protos */
#define RGP_SELF_AnimApplyMaterialKeys_154200 1
#define RGP_SELF_Apply 1
#define RGP_SELF_CopyXYZ 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#pragma optimization_level 3
#pragma opt_loop_invariants off
#pragma always_inline on

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz154200_t; /* rg:vu0bind vf0 */
#define vz154200 RG_VU0_BIND_VF(0, rgvb_vz154200_t)

typedef u128 __attribute__((aligned(4))) rgvb_va154200_t; /* rg:vu0bind vf1 */
#define va154200 RG_VU0_BIND_VF(1, rgvb_va154200_t)

typedef u128 __attribute__((aligned(4))) rgvb_vb154200_t; /* rg:vu0bind vf2 */
#define vb154200 RG_VU0_BIND_VF(2, rgvb_vb154200_t)


static inline void CopyXYZ(rg_vu0_state *rg_vu0_p_, void *d, void *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    u128 *pd = (u128 *)(u32)d;
    u128 *ps = (u128 *)(s32)(u32)s;
    ps = (u128 *)(s32)ps;
    va154200 = *pd;
    vb154200 = *ps;
    va154200 = _vaddbc(va154200, 0xE, vb154200, vz154200, 8);
    *pd = va154200;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
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

/*rgp*/
/*rgp*/
/*rgp*/

static inline void Apply(Node *n, Res *r)
{ RG_VU0_FRAME;
    n->dirty = 1;
    if (r->hasA != 0) {
        *(f32 *)((u8 *)n + 0x2C) = r->a;
    }
    if (r->hasB != 0) {
        CopyXYZ(&rg_vu0, &n->v20, &r->b);
    }
}

s32 AnimApplyMaterialKeys_154200(s32 o, s32 id, f32 t)
{
    Key *k;
    Node *n;
    Res r __attribute__((aligned(16)));

    if (o == 0) {
        return 0;
    }
    for (k = ((Key *)AnimResGetMaterialKeyList_14bef0(id)); k != 0; k = k->next) {
        n = ((Node *)ArrayGetChecked_153160(o, k->id));
        if (n != 0) {
            AnimKeyEvalMaterial_155af0(&r, k, t);
            Apply(n, &r);
        }
    }
    return 1;
}
