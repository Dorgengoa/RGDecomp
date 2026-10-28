/* rgp:protos */
#define RGP_SELF_CopyXYZ 1
#define RGP_SELF_ProjectileDrawModel_317640 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_s128 q;
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz317640_t; /* rg:vu0bind vf0 */
#define vz317640 RG_VU0_BIND_VF(0, rgvb_vz317640_t)

typedef u128 __attribute__((aligned(4))) rgvb_va317640_t; /* rg:vu0bind vf1 */
#define va317640 RG_VU0_BIND_VF(1, rgvb_va317640_t)

typedef u128 __attribute__((aligned(4))) rgvb_vb317640_t; /* rg:vu0bind vf2 */
#define vb317640 RG_VU0_BIND_VF(2, rgvb_vb317640_t)

typedef struct O { u8 pad0[0x100]; s32 x100; u8 pad104[0x1C]; u8 x120[1]; } O;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/* VU0 CopyXYZ (vaddx.xyz d,s,vf0x; vf0.x == 0): replaces d.xyz, keeps d.w.
   Asm-free (s88m): intrinsics on extern vf0/vf1/vf2 bindings; volatile loads keep
   the dest-then-source lqc2 order; optimization_level 3 keeps &m[3] in a GPR. */
static inline void CopyXYZ(rg_vu0_state *rg_vu0_p_, q *d, q *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    u128 *pd = (u128 *)d;
    u128 *ps = (u128 *)s;
    va317640 = *(volatile u128 *)pd;
    vb317640 = *(volatile u128 *)ps;
    va317640 = _vaddbc(va317640, 0xE, vb317640, vz317640, 8);
    *pd = va317640;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}
typedef struct S00317640 {
    u8 pad0[0x180];
    q pos;
    f32 scale;
    u8 pad194[0x2C];
    O *unk1C0;
} S00317640;
#pragma optimization_level 3
void ProjectileDrawModel_317640(S00317640 *arg0)
{ RG_VU0_FRAME;
    f32 m[4][4] __attribute__((aligned(16)));
    if (arg0->unk1C0 != NULL) {
        MtxIdentity_13d2e0(m);
        CopyXYZ(&rg_vu0, (q *)m[3], &arg0->pos);
        { f32 f = arg0->scale; m[0][0] = f; m[1][1] = f; m[2][2] = f; }
        ModelSetRootMatrix_1512e0(arg0->unk1C0, m);
        ModelDraw_14f6d0(arg0->unk1C0, GetDrawCtx_15de80(), arg0->unk1C0->x120);
        { O *p = arg0->unk1C0; p->x100 = 0; ModelDetachRootFrames_151460(p); }
    }
}
