/* rgp:protos */
#define RGP_SELF_AnimSlotApplyToMaterial_154540 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz154540_t; /* rg:vu0bind vf0 */
#define vz154540 RG_VU0_BIND_VF(0, rgvb_vz154540_t)

typedef u128 __attribute__((aligned(4))) rgvb_va154540_t; /* rg:vu0bind vf1 */
#define va154540 RG_VU0_BIND_VF(1, rgvb_va154540_t)

typedef u128 __attribute__((aligned(4))) rgvb_vb154540_t; /* rg:vu0bind vf2 */
#define vb154540 RG_VU0_BIND_VF(2, rgvb_vb154540_t)


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
{ RG_VU0_FRAME;
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
