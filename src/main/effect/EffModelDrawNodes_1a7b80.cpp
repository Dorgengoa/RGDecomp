#include "types.h"

typedef unsigned __int128 u128;

typedef struct M50 {
    u128 r[5];
} M50;

typedef struct Info {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    u8 x18[0x18];
} Info;

typedef struct Node {
    u8 pad0[0xC];
    struct Node *xC;
    u8 pad10[0xB0 - 0x10];
    s32 xB0;
} Node;

typedef struct Mdl {
    u8 pad0[0xA];
    u16 xA;
    u8 padC[0x20 - 0xC];
    u8 x20[0x10];
} Mdl;

class Drawer {
public:
    u8 pad0[0x50];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual s32 vf3(u128 *, void *);
    virtual s32 vf4(u128 *, void *, void *, s32);
};

typedef struct Self {
    u8 pad0[8];
    Mdl *x8;
    u8 padC[4];
    Drawer *x10;
} Self;

extern "C" {
s32 GetDrawCtx_15de80(void);
u128 *DrawListGetWritePtr_148a60(s32);
void MtxIdentityThunk_13d2e0(u128 *);
void MeshBuildParamInitMaybe_15c9b0(u128 *);
void DmaPktAddCallTag_141b80(s32, u128 *);
s32 DrawListWriteTexEnvPacket_148370(s32, u128 *, Mdl *);
void VuProgSelInitMaybe_14e410(Info *);
s32 ModelMeshGetVuVariantFlagsMaybe_14e430(Drawer *);
void CameraGetEyePos_13fce0(s32, u128 *);
void MtxLookAtKeepScale_13cc50(u128 *, u128 *);
void MtxYawFaceTarget_13cb30(u128 *, u128 *);
void VuProgSelResolveMaybe_14e370(Info *);
void XformPairComposeMatrix_19a0c0(Node *, u128 *, u128 *);
u128 *EffParticleGetMatrix_199f00(Node *);
void MtxMul_13d240(u128 *, u128 *, u128 *);
s32 VifPktUploadMatrix_148440(s32, u128 *, u128 *);
void VecMul_13bd40(u8 *, u128 *, u128 *);
s32 MeshPktWriteColourMaybe_14ab70(Mdl *, u128 *);
void XformPairSumUvOffset_19a150(Node *, u128 *);
s32 MeshPktWriteOffsetMaybe_14ab30(Mdl *, u128 *, u128 *);
void DrawCtxAddChangedCallTags_13fd70(s32, u8 *, s32);
void DmaPktAddMscalCall_145b20(s32, s32);
s32 DrawListCommitTo_1489f0(s32, u128 *);
s32 EffModelDrawNodes_1a7b80(Self *arg0, Node *arg1, M50 *arg2, s32 *arg3);
}

s32 EffModelDrawNodes_1a7b80(Self *arg0, Node *arg1, M50 *arg2, s32 *arg3) {
    u128 m210[4];
    u128 v1F0[2];
    u128 v1C0[3];
    Info v190;
    Info v160;
    u128 v150;
    u128 v140;
    u128 v100[4];
    u128 vF0;
    M50 mA0;
    s32 ctx;
    Mdl *mdl;
    s32 mode;
    s32 n;
    u128 *p;
    Drawer *drw;
    u128 *pkt;
    s32 pos;

    if (arg1 == 0) {
        return 0;
    }
    ctx = GetDrawCtx_15de80();
    mdl = arg0->x8;
    drw = arg0->x10;
    pkt = DrawListGetWritePtr_148a60(ctx);
    MtxIdentityThunk_13d2e0(m210);
    MeshBuildParamInitMaybe_15c9b0(v1F0);
    pos = arg1->xB0 >= 0;
        p = pkt;
        pkt += drw->vf3(pkt, v1F0);
        DmaPktAddCallTag_141b80(ctx, p);
    pkt += drw->vf4(pkt, v1C0, &v190, 10);
        p = pkt;
        pkt += DrawListWriteTexEnvPacket_148370(ctx, pkt, mdl);
        DmaPktAddCallTag_141b80(ctx, p);
    VuProgSelInitMaybe_14e410(&v160);
    v160.x0 = mdl->xA;
    v160.x8 = ModelMeshGetVuVariantFlagsMaybe_14e430(drw);
    CameraGetEyePos_13fce0(ctx, &vF0);
    mA0.r[0] = arg2->r[0];
    mA0.r[1] = arg2->r[1];
    mA0.r[2] = arg2->r[2];
    mA0.r[3] = arg2->r[3];
    mA0.r[4] = arg2->r[4];
    mode = arg3[0];
    if (mode != 0) {
        if (mode == 1) {
            MtxLookAtKeepScale_13cc50(mA0.r, &vF0);
        } else {
            MtxYawFaceTarget_13cb30(mA0.r, &vF0);
        }
    }
    VuProgSelResolveMaybe_14e370(&v160);
    while (arg1 != 0) {
        XformPairComposeMatrix_19a0c0(arg1, v100, &v150);
        if (pos) {
            MtxMul_13d240(m210, EffParticleGetMatrix_199f00(arg1), v100);
        } else {
            MtxMul_13d240(m210, mA0.r, v100);
        }
        mode = arg3[1];
        if (mode != 0) {
            if (mode == 1) {
                MtxLookAtKeepScale_13cc50(m210, &vF0);
            } else {
                MtxYawFaceTarget_13cb30(m210, &vF0);
            }
        }
        p = pkt;
        pkt += VifPktUploadMatrix_148440(ctx, pkt, m210);
        DmaPktAddCallTag_141b80(ctx, p);
        VecMul_13bd40(mdl->x20, &v150, &mA0.r[4]);
        p = pkt;
        pkt += MeshPktWriteColourMaybe_14ab70(mdl, pkt);
        DmaPktAddCallTag_141b80(ctx, p);
        XformPairSumUvOffset_19a150(arg1, &v140);
        p = pkt;
        pkt += MeshPktWriteOffsetMaybe_14ab30(mdl, pkt, &v140);
        DmaPktAddCallTag_141b80(ctx, p);
        DrawCtxAddChangedCallTags_13fd70(ctx, v160.x18, v160.x14);
        DmaPktAddMscalCall_145b20(ctx, v190.x0);
        arg1 = arg1->xC;
    }
    return DrawListCommitTo_1489f0(ctx, pkt);
}
