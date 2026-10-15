#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct {
    u128 q[4];
    s32 unk40;
    u8 pad44[0x60 - 0x44];
} Desc;

typedef struct {
    u8 pad0[0xC];
    s16 *unkC;
    u8 pad10[0x40 - 0x10];
    void *unk40;
} Mesh;

typedef struct {
    u8 pad0[0x4];
    s32 unk4;
    Mesh *unk8;
    u8 padC[0x130 - 0xC];
    V4 min;
    V4 max;
    V4 uv;
} Obj;

typedef struct {
    u8 pad0[0x20];
} Iter;

extern void BoundsFrom4Points_13df00(V4 *, V4 *, V4 *, V4 *, V4 *, V4 *);
extern void MeshMaterialBuildPkt_14ac90(Mesh *, Desc *, s32, s32);
extern void ModelResGetMeshInfo_14c440(Iter *, s32, s32);
extern s32 ModelResGetMeshCount_14c5c0(s32);
extern Desc *ArrayGetChecked_14c5e0(s32, s32);
extern void ModelReadUVs_14c870(Iter *, V4 *, s32, s32);
extern void ModelReadVertices_14c9f0(Iter *, V4 *, s32, s32);
extern Mesh *MemStackNew_14e230(s32, s32);
extern s32 GetDrawCtx_15de80(void);
extern u8 D_0046FF90[];
extern f32 D_0047D42C;

void EffQuadResInitFromMds_1a7e70(Obj *arg0, s32 arg1, s32 arg2)
{
    Desc d;
    Iter it;
    V4 pts[4];
    V4 uv[4];
    V4 u1;
    V4 u0;
    V4 b1;
    V4 b0;
    s32 ctx;
    Mesh *m;
    f32 f;

    ctx = GetDrawCtx_15de80();
    m = MemStackNew_14e230(0x50, arg2);
    if (m != NULL) {
        m->unk40 = D_0046FF90;
    }
    arg0->unk8 = m;
    d = *ArrayGetChecked_14c5e0(arg1, 0);
    d.unk40 = 5;
    MeshMaterialBuildPkt_14ac90(arg0->unk8, &d, arg2, ctx);
    if (arg0->unk8->unkC != NULL) {
        arg0->unk4 = *arg0->unk8->unkC;
    }
    if (ModelResGetMeshCount_14c5c0(arg1) > 0) {
        ModelResGetMeshInfo_14c440(&it, arg1, 0);
        ModelReadVertices_14c9f0(&it, pts, 4, 0);
        ModelReadUVs_14c870(&it, uv, 4, 0);
        *(u128 *)&arg0->min = *(u128 *)&pts[0];
        *(u128 *)&arg0->max = *(u128 *)&pts[3];
        f = (arg0->max.x - arg0->min.x) * (arg0->max.z - arg0->min.z);
        f = (f < 0.0f) ? -f : f;
        if (f < D_0047D42C) {
            BoundsFrom4Points_13df00(&u0, &u1, &pts[0], &pts[1], &pts[2], &pts[3]);
            arg0->min.x = u1.x;
            arg0->min.y = u1.y;
            arg0->min.z = u1.z;
            arg0->max.x = u0.x;
            arg0->max.y = u0.y;
            arg0->max.z = u0.z;
        }
        arg0->min.w = 1.0f;
        arg0->max.w = 1.0f;
        arg0->uv.x = uv[0].x;
        arg0->uv.y = uv[0].y;
        arg0->uv.z = uv[3].x;
        arg0->uv.w = uv[3].y;
        f = (arg0->uv.z - arg0->uv.x) * (arg0->uv.w - arg0->uv.y);
        f = (f < 0.0f) ? -f : f;
        if (f < D_0047D42C) {
            BoundsFrom4Points_13df00(&b0, &b1, &uv[0], &uv[1], &uv[2], &uv[3]);
            arg0->uv.x = b1.x;
            arg0->uv.y = b1.y;
            arg0->uv.z = b0.x;
            arg0->uv.w = b0.y;
        }
    } else {
        arg0->min.x = -1.0f;
        arg0->min.y = -1.0f;
        arg0->min.z = 0.0f;
        arg0->min.w = 1.0f;
        arg0->max.x = 1.0f;
        arg0->max.y = 1.0f;
        arg0->max.z = 0.0f;
        arg0->max.w = 1.0f;
        arg0->uv.x = 0.0f;
        arg0->uv.y = 0.0f;
        arg0->uv.z = 1.0f;
        arg0->uv.w = 1.0f;
    }
}
