/* rg-override: replaces game/src/main/model/CollFrameTreeCollectTris_16bfb0.cpp sha256 e0f97f5461e288025f55441cf48169dde85c063d7b7909bbb9a62fc8a395b8a0
 * why: cross-file VU0 register protocol (loads the matrix vf10-13 that CollTriTransform_16c1a0 reads); with RG_VU0_LOCAL the file
 * shares the named context `colltri` (port/vu0_ctx.h, docs/NATIVE-CPU.md); otherwise verbatim */
#define RG_VU0_CTX_NAME colltri
#include "port/vu0_ctx.h"
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "vec.h"

/* VU0 matrix load as mwcc intrinsic register bindings (no inline-assembly block): vf10-vf13 stay
 * loaded for CollTriTransform_16c1a0. The empty `if (pm) { pm = launder(pm); }` emits no code but keeps the
 * block boundary the retail assembly block made; opt_propagation off keeps pm in a register. */
#pragma vu0_mmi_reg_binding on
typedef rg_u128 __attribute__((aligned(4))) rgvb_m0_16bfb0_t; /* rg:vu0bind vf10 */
#define m0_16bfb0 RG_VU0_BIND_VF(10, rgvb_m0_16bfb0_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_m1_16bfb0_t; /* rg:vu0bind vf11 */
#define m1_16bfb0 RG_VU0_BIND_VF(11, rgvb_m1_16bfb0_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_m2_16bfb0_t; /* rg:vu0bind vf12 */
#define m2_16bfb0 RG_VU0_BIND_VF(12, rgvb_m2_16bfb0_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_m3_16bfb0_t; /* rg:vu0bind vf13 */
#define m3_16bfb0 RG_VU0_BIND_VF(13, rgvb_m3_16bfb0_t)


class Handler {
    u8 pad0[0x30];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    s32 run(s32 a0, u8 * a1, Vec4 * a2, s32 a3) { return VCM(s32, (void *, s32, u8 *, Vec4 *, s32), 0x30, a0, a1, a2, a3); }
};

struct Node0016bfb0 {
    u8 pad0[8];
    Node0016bfb0 *unk8;
    Node0016bfb0 *unkC;
    u8 pad10[0xF0 - 0x10];
    u32 unkF0;
    Handler *unkF4;
};


extern "C" {
void FrameCalcWorldMatrix_148ff0(Node0016bfb0 *, Mtx4 *);
void FrameCalcInvWorldMatrix_148fb0(Node0016bfb0 *, Mtx4 *);
void AabbTransformBounds_13c710(Vec4 *, Vec4 *, Mtx4 *, s32, Vec4 *);
void CollTriTransform_16c1a0(u8 *, u8 *, u8 *, u8 *);
s32 CollFrameTreeCollectTris_16bfb0(Node0016bfb0 *arg0, s32 arg1, u8 *arg2, Vec4 *arg3, s32 arg4);
}

#pragma optimization_level 3
#pragma opt_propagation off
extern "C" s32 CollFrameTreeCollectTris_16bfb0(Node0016bfb0 *arg0, s32 arg1, u8 *arg2, Vec4 *arg3, s32 arg4)
{
    Mtx4 m110 __attribute__((aligned(16)));
    Mtx4 mD0 __attribute__((aligned(16)));
    Vec4 vC0 __attribute__((aligned(16)));
    Vec4 vB0 __attribute__((aligned(16)));
    Vec4 vA0 __attribute__((aligned(16)));
    Vec4 v90 __attribute__((aligned(16)));
    u32 fl;
    u128 qa;
    u128 qb;
    u8 *cur;
    s32 i;
    s32 r;
    s32 n;
    Node0016bfb0 *c;
    Mtx4 *pm;

    cur = arg2;
    fl = arg0->unkF0;
    n = 0;
    if (fl == 2) {
        return 0;
    }
    if (arg0->unkF4 != 0 && (fl & 1)) {
        FrameCalcWorldMatrix_148ff0(arg0, &m110);
        FrameCalcInvWorldMatrix_148fb0(arg0, &mD0);
        qa = *(u128 *)&arg3[0];
        qb = *(u128 *)&arg3[1];
        *(u128 *)&v90 = qa;
        *(u128 *)&vA0 = qb;
        v90.w = 1.0f;
        vA0.w = 1.0f;
        AabbTransformBounds_13c710(&vB0, &vC0, &mD0, (s32)&v90, &vA0);
        n = arg0->unkF4->run(arg1, arg2, &vB0, arg4);
        pm = &m110;
        arg4 -= n;
        if (pm) { pm = (Mtx4 *)(s32)(u32)pm; }
        m0_16bfb0 = ((rg_u128 *)pm)[0];
        m1_16bfb0 = ((rg_u128 *)pm)[1];
        m2_16bfb0 = ((rg_u128 *)pm)[2];
        m3_16bfb0 = ((rg_u128 *)pm)[3];
        for (i = 0; i < n; i++, cur += 0x60) {
            CollTriTransform_16c1a0(cur, cur + 0x10, cur + 0x20, cur + 0x30);
        }
    }
    if (arg4 <= 0) {
        return n;
    }
    {
        if (!(arg0->unkF0 & 2))
        for (c = arg0->unk8; c != 0; c = c->unkC) {
            if (arg0->unkF0 & 4) {
                continue;
            }
            r = CollFrameTreeCollectTris_16bfb0(c, arg1, cur, arg3, arg4);
            n += r;
            arg4 -= r;
            cur = arg2 + n * 0x60;
            if (arg4 <= 0) {
                break;
            }
        }
    }
    return n;
}
