#include "types.h"

typedef unsigned __int128 u128;
struct Blk96 {
    u128 q[6];
};

struct Info {
    u8 pad0[0x14];
    s32 n;
    u8 pad18[8];
};

struct Sub8 {
    u8 pad0[0xC];
    s16 *xC;
};

struct Self {
    s32 x0;
    s32 x4;
    Sub8 *x8;
    u8 *xC;
    s32 x10;
    s32 x14;
    s32 x18;
};

extern "C" {
s32 MeshMaterialBuildPkt_14ac90(Sub8 *, Blk96 *, s32, s32);
void ModelResGetMeshInfo_14c440(Info *, s32, s32);
Blk96 *ArrayGetChecked_14c5e0(s32, s32);
s32 ArrayGetChecked_14c7f0(s32, s32);
void ModelReadVertices_14c9f0(Info *, s32, s32, s32);
s32 MemStackNew_14e1b0(s32, s32);
void *MemStackNew_14e230(s32, s32);
s32 ModelMeshCreate_14e4d0(Info *, s32, s32);
void FrameInitFromRes_14e710(u8 *, s32, s32);
s32 GetDrawCtx_15de80();
extern u8 D_0046FF90[0x40];
extern u8 D_0046FFA0[0x40];
}

struct ObjBase {
    u8 pad0[0xE0];
};

struct Obj : ObjBase {
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

extern "C" void EffModelResInitFromMds_1a81e0(Self *self, s32 arg1, s32 arg2)
{
    s32 h;
    u8 *p;
    u8 *q;
    s16 *v;
    Blk96 m;
    Info info;

    h = GetDrawCtx_15de80();
    p = (u8 *)MemStackNew_14e230(0xF0, arg2);
    if (p != NULL) {
        *(u8 **)(p + 0xE0) = D_0046FFA0;
        ((Obj *)p)->f2();
    }
    self->xC = p;
    q = (u8 *)MemStackNew_14e230(0x50, arg2);
    if (q != NULL) {
        *(u8 **)(q + 0x40) = D_0046FF90;
    }
    self->x8 = (Sub8 *)q;
    FrameInitFromRes_14e710(self->xC, ArrayGetChecked_14c7f0(arg1, 0), arg2);
    m = *ArrayGetChecked_14c5e0(arg1, 0);
    MeshMaterialBuildPkt_14ac90(self->x8, &m, arg2, h);
    v = self->x8->xC;
    if (v != NULL) {
        self->x4 = *v;
    }
    ModelResGetMeshInfo_14c440(&info, arg1, 0);
    self->x10 = ModelMeshCreate_14e4d0(&info, arg2, h + 0xD0);
    self->x18 = MemStackNew_14e1b0(info.n << 4, arg2);
    if (self->x18 != 0) {
        self->x14 = info.n;
        ModelReadVertices_14c9f0(&info, self->x18, self->x14, 0);
    }
}
