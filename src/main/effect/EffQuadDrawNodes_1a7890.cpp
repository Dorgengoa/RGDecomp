#include "types.h"
#include "vec.h"

typedef struct Base50 { u8 pad[0x50]; } Base50;
class Obj : public Base50 {
public:
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual s32 build(u128 *p, void *arg);
};

typedef struct Node { u8 pad0[0xC]; struct Node *next; u8 pad1[0xB0 - 0x10]; s32 mB0; } Node;
typedef struct Hdr { u8 pad[0xA]; u16 mA; } Hdr;
typedef struct Pkt { s32 m0; u8 pad[0x10]; s32 m14; u8 m18[0x18]; } Pkt;
typedef struct A { u8 pad[8]; Hdr *m8; } A;

extern "C" {
s32 GetDrawCtx_15de80(void);
u128 *DrawListGetWritePtr_148a60(s32 g);
void MtxIdentityThunk_13d2e0(Mtx4 *m);
s32 VifPktUploadMatrix_148440(s32 g, u128 *p, Mtx4 *m);
void DmaPktAddCallTag_141b80(s32 g, u128 *p);
void MeshBuildParamInitMaybe_15c9b0(void *p);
void PrimBatchSetBuffer_1645b0(Obj *o, u128 *p);
s32 PrimBatchCapacity_164580(Obj *o);
void PrimBatchBegin_164320(Obj *o, s32 a, s32 b);
void XformPairSumPos_19a1d0(Node *n, Vec4 *v);
void XformPairSumRot_19a1b0(Node *n, Vec4 *v);
void XformPairMulScale_19a190(Node *n, Vec4 *v);
void XformPairMulColor_19a170(Node *n, Vec4 *v);
void XformPairSumUvOffset_19a150(Node *n, Vec4 *v);
void VecMul_13bd40(Vec4 *d, Vec4 *a, Vec4 *b);
Vec4 *EffParticleGetMatrix_199f00(Node *n);
void MtxMulPoint_13c890(Vec4 *d, Vec4 *a, Vec4 *b);
f32 VecLength_13d4a0(Vec4 *v);
void VecAdd_13be20(Vec4 *d, Vec4 *a, Vec4 *b);
void PrimBatchAddVertex_164130(Obj *o, Vec4 *a, Vec4 *b, Vec4 *c, Vec4 *d, Vec4 *e);
void PrimBatchClose_1642a0(Obj *o);
s32 PrimBatchTerminate_164530(Obj *o);
s32 DrawListWriteTexEnvPacket_148370(s32 g, u128 *p, Hdr *h);
void VuProgSelInitMaybe_14e410(Pkt *k);
void VuProgSelResolveMaybe_14e370(Pkt *k);
void DrawCtxAddChangedCallTags_13fd70(s32 g, void *a, s32 b);
void DmaPktAddMscalCall_145b20(s32 g, u128 *p);
s32 DrawListCommitTo_1489f0(s32 g, u128 *p);
}

extern "C" s32 EffQuadDrawNodes_1a7890(A *a, Node *n, Vec4 *m)
{
    Mtx4 mtx;
    u8 tmp[0x20];
    Vec4 pos;
    Vec4 v120;
    Vec4 scl;
    Vec4 v100;
    Vec4 vF0;
    Vec4 vE0;
    Pkt pk;
    s32 g;
    u128 *p;
    Hdr *h;
    Obj *obj;
    u128 *q;
    u128 *base;
    s32 flag;

    if (n == 0) {
        return 0;
    }
    g = GetDrawCtx_15de80();
    p = DrawListGetWritePtr_148a60(g);
    h = a->m8;
    MtxIdentityThunk_13d2e0(&mtx);
    mtx.r[0] = m[0];
    mtx.r[1] = m[1];
    mtx.r[2] = m[2];
    mtx.r[3] = m[3];
    q = p;
    p += VifPktUploadMatrix_148440(g, p, &mtx);
    DmaPktAddCallTag_141b80(g, q);
    obj = (Obj *)((u8 *)a + 0x10);
    MeshBuildParamInitMaybe_15c9b0(tmp);
    q = p;
    p += obj->build(p, tmp);
    DmaPktAddCallTag_141b80(g, q);
    flag = n->mB0 >= 0;
    base = p;
    PrimBatchSetBuffer_1645b0(obj, p);
    PrimBatchBegin_164320(obj, 0x20, PrimBatchCapacity_164580(obj));
    while (n != 0) {
        XformPairSumPos_19a1d0(n, &pos);
        XformPairSumRot_19a1b0(n, &v120);
        XformPairMulScale_19a190(n, &scl);
        XformPairMulColor_19a170(n, &v100);
        VecMul_13bd40(&v100, &v100, &m[4]);
        if (flag) {
            Vec4 *r = EffParticleGetMatrix_199f00(n);
            MtxMulPoint_13c890(&pos, r, &pos);
            scl.x *= VecLength_13d4a0(&r[0]);
            scl.y *= VecLength_13d4a0(&r[1]);
        } else {
            scl.x *= VecLength_13d4a0(&m[0]);
            scl.y *= VecLength_13d4a0(&m[1]);
        }
        scl.z = v120.z;
        XformPairSumUvOffset_19a150(n, &vE0);
        vE0.z = vE0.x;
        vE0.w = vE0.y;
        VecAdd_13be20(&vF0, (Vec4 *)((u8 *)a + 0x150), &vE0);
        PrimBatchAddVertex_164130(obj, &pos, &scl, (Vec4 *)((u8 *)a + 0x130), &vF0, &v100);
        n = n->next;
    }
    PrimBatchClose_1642a0(obj);
    p += PrimBatchTerminate_164530(obj);
    q = p;
    p += DrawListWriteTexEnvPacket_148370(g, q, h);
    DmaPktAddCallTag_141b80(g, q);
    VuProgSelInitMaybe_14e410(&pk);
    pk.m0 = h->mA;
    VuProgSelResolveMaybe_14e370(&pk);
    DrawCtxAddChangedCallTags_13fd70(g, pk.m18, pk.m14);
    DmaPktAddCallTag_141b80(g, q);
    DmaPktAddMscalCall_145b20(g, base);
    return DrawListCommitTo_1489f0(g, p);
}
