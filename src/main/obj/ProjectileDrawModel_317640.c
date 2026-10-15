#include "types.h"
typedef __int128 q;
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 vz317640 asm("vf0");
extern u128 va317640 asm("vf1");
extern u128 vb317640 asm("vf2");
typedef struct O { u8 pad0[0x100]; s32 x100; u8 pad104[0x1C]; u8 x120[1]; } O;
extern void MtxIdentity_13d2e0(f32 m[4][4]);
extern void *ModelDraw_14f6d0(O *arg0, s32 arg1, void *arg2);
extern void ModelSetRootMatrix_1512e0(O *arg0, f32 m[4][4]);
extern void ModelDetachRootFrames_151460(O *arg0);
extern s32 GetDrawCtx_15de80(void);
/* VU0 CopyXYZ (vaddx.xyz d,s,vf0x; vf0.x == 0): replaces d.xyz, keeps d.w.
   Asm-free (s88m): intrinsics on extern vf0/vf1/vf2 bindings; volatile loads keep
   the dest-then-source lqc2 order; optimization_level 3 keeps &m[3] in a GPR. */
static inline void CopyXYZ(q *d, q *s)
{
    u128 *pd = (u128 *)d;
    u128 *ps = (u128 *)s;
    va317640 = *(volatile u128 *)pd;
    vb317640 = *(volatile u128 *)ps;
    va317640 = _vaddbc(va317640, 0xE, vb317640, vz317640, 8);
    *pd = va317640;
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
{
    f32 m[4][4];
    if (arg0->unk1C0 != NULL) {
        MtxIdentity_13d2e0(m);
        CopyXYZ((q *)m[3], &arg0->pos);
        { f32 f = arg0->scale; m[0][0] = f; m[1][1] = f; m[2][2] = f; }
        ModelSetRootMatrix_1512e0(arg0->unk1C0, m);
        ModelDraw_14f6d0(arg0->unk1C0, GetDrawCtx_15de80(), arg0->unk1C0->x120);
        { O *p = arg0->unk1C0; p->x100 = 0; ModelDetachRootFrames_151460(p); }
    }
}
