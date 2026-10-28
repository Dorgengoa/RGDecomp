/* rg-override: replaces game/src/main/matrix/CameraBaseLookAt_15fae0.cpp sha256 400fec9b78f5a9ed0c676a3459a2d405395d8863ce65f439565fa15335395d42
 * why: side/up/dir(/old) are ONE retail 4-row matrix at sp+0x80..0xBF (MtxMul_13d240 and
 * the setDir virtual read it as rows); separate clang locals put them in another order,
 * so every camera's basis was wrong (sky-only field, docs/RENDER-BRINGUP.md). The
 * stack-block stage declined it (coverage guard: `up` row) -- this places the block. */
#include "port/vu0intrin.h" /* rg:vu0bind */
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
    VC_VPTR_MEMBER;
    
    
    
    
    void setDir(Vec4 *d) { VCM(void, (void *, Vec4 *), 0x1C, d); }
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
typedef u128 __attribute__((aligned(4))) rgvb_vz15fae0_t; /* rg:vu0bind vf0 */
#define vz15fae0 RG_VU0_BIND_VF(0, rgvb_vz15fae0_t)

typedef u128 __attribute__((aligned(4))) rgvb_va15fae0_t; /* rg:vu0bind vf1 */
#define va15fae0 RG_VU0_BIND_VF(1, rgvb_va15fae0_t)

typedef u128 __attribute__((aligned(4))) rgvb_vb15fae0_t; /* rg:vu0bind vf2 */
#define vb15fae0 RG_VU0_BIND_VF(2, rgvb_vb15fae0_t)


extern "C" void CameraBaseLookAt_15fae0(Cam *c, Vec4 *eye, Vec4 *at, f32 roll)
{ RG_VU0_FRAME;
    struct { Vec4 side, up, dir, old; } blk __attribute__((aligned(16))); /* sp+0x80 */
    Mtx4 m __attribute__((aligned(16)));
#define side blk.side
#define up blk.up
#define dir blk.dir
#define old blk.old

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
#undef side
#undef up
#undef dir
#undef old
