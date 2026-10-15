#include "types.h"
#include "vec.h"

/* VU0 matrix load as mwcc intrinsic register bindings (no inline-assembly block): vf10-vf13 stay
 * loaded for CollTriTransform_16c1a0. The empty `if (pm) { pm = launder(pm); }` emits no code but keeps the
 * block boundary the retail assembly block made; opt_propagation off keeps pm in a register. */
#pragma vu0_mmi_reg_binding on
extern unsigned __int128 m0_16bfb0 asm("vf10");
extern unsigned __int128 m1_16bfb0 asm("vf11");
extern unsigned __int128 m2_16bfb0 asm("vf12");
extern unsigned __int128 m3_16bfb0 asm("vf13");

class Handler {
    u8 pad0[0x30];
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual s32 run(s32, u8 *, Vec4 *, s32);
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
    Mtx4 m110;
    Mtx4 mD0;
    Vec4 vC0;
    Vec4 vB0;
    Vec4 vA0;
    Vec4 v90;
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
        m0_16bfb0 = ((unsigned __int128 *)pm)[0];
        m1_16bfb0 = ((unsigned __int128 *)pm)[1];
        m2_16bfb0 = ((unsigned __int128 *)pm)[2];
        m3_16bfb0 = ((unsigned __int128 *)pm)[3];
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
