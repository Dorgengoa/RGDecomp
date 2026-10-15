#include "types.h"
#include "vec.h"
/* CameraBaseLookAt_15fae0 -- camera look-at: forward = normalize(eye - at), side = up x fwd
 * (skipped when degenerate), optional roll about Z, then the virtual setDir and the
 * basis rebuild/renormalise; finally pos.xyz = eye.xyz (vaddx.xyz with vf0.x).
 * Asm-free (s88m, was a whole-function asm source):
 * - .cpp: `jalr $25` is a C++ virtual call (vptr at 0xC0, slot 0x1C);
 * - mwcc VU0 intrinsics on `extern` vf0/vf1/vf2 bindings; volatile qword loads keep
 *   the lqc2 pos-then-eye order, the zero-word split on eye keeps them out of the
 *   bc1t delay slot;
 * - `old` (a dead copy of the position) holds the unused 16-byte frame slot at 0xB0. */

class Cam {
public:
    Vec4 r0;
    Vec4 x;
    Vec4 y;
    Vec4 z;
    Vec4 pos;
    u8 pad50[0x70];
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void setDir(Vec4 *d);
};

extern "C" {
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void sceVu0OuterProduct(Vec4 *, Vec4 *, Vec4 *);
extern f32 VecLength_13d4a0(Vec4 *);
extern void MtxIdentity_13d2e0(Mtx4 *);
extern f32 WrapAngle_13c050(f32);
extern void sceVu0RotMatrixZ(Mtx4 *, Mtx4 *, f32);
extern void MtxMul_13d240(Vec4 *, Vec4 *, Mtx4 *);
extern f32 D_0047D258;
}

#pragma vu0_mmi_reg_binding on
extern u128 vz15fae0 asm("vf0");
extern u128 va15fae0 asm("vf1");
extern u128 vb15fae0 asm("vf2");

extern "C" void CameraBaseLookAt_15fae0(Cam *c, Vec4 *eye, Vec4 *at, f32 roll)
{
    Vec4 old;
    Vec4 dir;
    Vec4 up;
    Vec4 side;
    Mtx4 m;

    VEC4_ZERO(up);
    up.y = 1.0f;
    VecSub_13be40(&dir, eye, at);
    VecNormalize_13bd90(&dir, &dir);
    sceVu0OuterProduct(&side, &up, &dir);
    if (VecLength_13d4a0(&side) > D_0047D258) {
        sceVu0OuterProduct(&up, &dir, &side);
        if (roll != 0.0f) {
            MtxIdentity_13d2e0(&m);
            sceVu0RotMatrixZ(&m, &m, WrapAngle_13c050(roll));
            MtxMul_13d240(&side, &side, &m);
        }
        c->setDir(&side);
        sceVu0OuterProduct(&c->z, &c->x, &c->y);
        sceVu0OuterProduct(&c->x, &c->y, &c->z);
        VecNormalize_13bd90(&c->x, &c->x);
        VecNormalize_13bd90(&c->y, &c->y);
        VecNormalize_13bd90(&c->z, &c->z);
    }
    old = c->pos;
    if (eye) { eye = (Vec4 *)(s32)(u32)eye; }
    va15fae0 = *(volatile u128 *)&c->pos;
    vb15fae0 = *(volatile u128 *)eye;
    va15fae0 = _vaddbc(va15fae0, 0xE, vb15fae0, vz15fae0, 8);
    *(u128 *)&c->pos = va15fae0;
}
