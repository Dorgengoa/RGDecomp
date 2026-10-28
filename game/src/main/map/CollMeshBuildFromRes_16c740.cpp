/* rgp:protos */
#line 1
#pragma optimization_level 3
#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct {
    s32 n;
    u8 *data;
} Hdr;

typedef struct Node {
    struct Node *next;
    u16 type;
    u16 count;
    u8 flag;
    u8 pad9[3];
    u32 *mat;
    u16 *idx;
} Node;

typedef struct {
    s16 v[4];
    s16 flags;
    s16 t[3];
} Out;

typedef struct {
    f32 v[4];
    f32 t[4];
    f32 f20;
    f32 f24;
} Src;

class Obj {
public:
    u8 pad0[0x30];
    VC_VPTR_MEMBER;
    
    
    
    void v18() { VCM0(void, 0x18); }
    u8 pad34[0x40 - 0x34];
    s32 nverts;
    u8 *verts;
    s32 nout;
    Out *outs;
    s32 ntris;
    u16 *tris;
};

extern "C" {
extern f32 VecLength_13d4a0(V4 *);
extern void VecTriCross_13de70(V4 *, V4 *, V4 *, V4 *);
extern void VertexDecodeS8_14b3a0(V4 *, u8 *, u8 *);
extern void VertexDecodeS16_14b410(V4 *, u8 *, u8 *);
extern void VertexDecodeF32_14b4a0(V4 *, u8 *);
extern Src *ArrayGetChecked_14c5e0(s32, s32);
extern s32 ModelResGetMaterialCount_14c640(s32);
extern void ModelResGetPosScale_14ccb0(s32, u8 *);
extern s32 ModelResGetPosFormat_14cd70(s32);
extern Node *ModelResGetPrimGroupList_14ce20(s32);
extern s32 ModelResGetPrimGroupCount_14ce40(s32);
extern Hdr *ModelResGetVertexBufMaybe_14ce60(s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern void CollMeshBuildQuadTree_16c210(Obj *, s32, int, int);
extern void *memset(void *, s32, u32);
}

extern "C" void CollMeshBuildFromRes_16c740(Obj *self, s32 arg1, s32 arg2, s32 heap)
{
    u8 ctx[0x10] __attribute__((aligned(16)));
    V4 v8 __attribute__((aligned(16)));
    V4 v16 __attribute__((aligned(16)));
    V4 v32 __attribute__((aligned(16)));
    V4 tri[3] __attribute__((aligned(16)));
    V4 nrm __attribute__((aligned(16)));
    Hdr *hdr;
    s32 n;
    u8 *data;
    u8 *dd; /* hdr->data; copied into data below so data colours before fmt */
    s32 fmt;
    s32 cnt;
    s32 i;
    V4 *dv;
    s32 m;
    Out *o;
    Src *s;
    Node *nd;
    s32 total;
    u16 *out;
    u16 *idx;
    u32 *mat;
    s32 k;
    s32 c;
    V4 *sv;

    hdr = ModelResGetVertexBufMaybe_14ce60(arg2);
    if (hdr == NULL) {
        return;
    }
    n = hdr->n;
    if (n <= 0) {
        return;
    }
    dd = hdr->data;
    ModelResGetPosScale_14ccb0(arg2, ctx);
    fmt = ModelResGetPosFormat_14cd70(arg2);
    if (fmt != 8 && fmt != 0x10 && fmt != 0x20) {
        return;
    }
    cnt = ModelResGetPrimGroupCount_14ce40(arg2);
    if (cnt <= 0) {
        return;
    }
    self->verts = (u8 *)MemStackNew_14e1b0(n * 0xC, heap);
    if (self->verts == NULL) {
        return;
    }
    self->nverts = n;
    data = dd;
    switch (fmt) {
    case 8:
        for (i = 0; i < n; i++) {
            VertexDecodeS8_14b3a0(&v8, data + i * 3, ctx);
            dv = (V4 *)(self->verts + i * 0xC);
            dv->x = v8.x;
            dv->y = v8.y;
            dv->z = v8.z;
            dv->w = 1.0f;
        }
        break;
    case 0x10:
        for (i = 0; i < n; i++) {
            VertexDecodeS16_14b410(&v16, data + i * 6, ctx);
            dv = (V4 *)(self->verts + i * 0xC);
            dv->x = v16.x;
            dv->y = v16.y;
            dv->z = v16.z;
            dv->w = 1.0f;
        }
        break;
    case 0x20:
        for (i = 0; i < n; i++) {
            VertexDecodeF32_14b4a0(&v32, data + i * 0xC);
            dv = (V4 *)(self->verts + i * 0xC);
            dv->x = v32.x;
            dv->y = v32.y;
            dv->z = v32.z;
            dv->w = 1.0f;
        }
        break;
    }
    m = ModelResGetMaterialCount_14c640(arg1);
    self->outs = (Out *)MemStackNew_14e1b0(m * 0x10, heap);
    if (self->outs == NULL) {
        return;
    }
    self->nout = m;
    for (i = 0; i < m; i++) {
        s = ArrayGetChecked_14c5e0(arg1, i);
        o = &self->outs[i];
        memset(o, 0, 0x10);
        if (s == NULL) {
            continue;
        }
        o->v[0] = 0.0001f + s->v[0];
        o->v[1] = 0.0001f + s->v[1];
        o->v[2] = 0.0001f + s->v[2];
        o->v[3] = 1.0f - s->v[3];
        if (!(s->f20 <= 0.99f)) {
            o->flags |= 1;
        }
        if (!(s->f24 <= 0.99f)) {
            o->flags |= 2;
        }
        o->t[0] = 0.0001f + s->t[0];
        o->t[1] = 0.0001f + s->t[1];
        o->t[2] = 0.0001f + s->t[2];
    }
    nd = ModelResGetPrimGroupList_14ce20(arg2);
    total = 0;
    for (; cnt > 0 && nd != NULL; nd = nd->next) {
        c = nd->count;
        if (nd->type == 3) {
            total += c / 3;
        }
    }
    if (total <= 0) {
        return;
    }
    self->tris = (u16 *)MemStackNew_14e1b0(total * 0xC, heap);
    if (self->tris == NULL) {
        return;
    }
    self->ntris = 0;
    nd = ModelResGetPrimGroupList_14ce20(arg2);
    out = self->tris;
    for (; cnt > 0 && nd != NULL; nd = nd->next) {
        m = nd->count;
        if (nd->type != 3) {
            continue;
        }
        mat = nd->mat;
        if (nd->flag <= 0) {
            continue;
        }
        if (!(*mat < (u32)self->nout)) {
            continue;
        }
        idx = nd->idx;
        for (i = 0; i < m; i += 3) {
            for (k = 0; k < 3; k++) {
                out[k + 1] = idx[k];
                sv = (V4 *)(self->verts + idx[k] * 0xC);
                tri[k].x = sv->x;
                tri[k].y = sv->y;
                tri[k].z = sv->z;
                tri[k].w = 1.0f;
            }
            VecTriCross_13de70(&nrm, &tri[0], &tri[1], &tri[2]);
            idx += 3;
            if (VecLength_13d4a0(&nrm) < 0.0001f) {
                continue;
            }
            out[0] = *mat;
            self->ntris++;
            out += 6;
        }
    }
    self->v18();
    CollMeshBuildQuadTree_16c210(self, heap, 0, 0);
}
