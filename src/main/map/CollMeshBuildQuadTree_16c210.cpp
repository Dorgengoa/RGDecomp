#pragma opt_lifetimes off
#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct {
    Vec4 min;
    Vec4 max;
} Box;

typedef struct {
    Vec4 c;
    u16 x10;
    u16 x12;
    s32 x14[4];
} Sub;

typedef struct {
    Sub *sub;
    f32 x4;
    f32 x8;
    s32 heap;
} Node;

typedef struct {
    u16 x0;
    u16 a;
    u16 b;
    u16 c;
    Sub *x8;
} Tri;

struct ObjBase {
    u8 pad0[0x30];
};

class Obj : public ObjBase {
public:
    virtual void v0();
    virtual void v1();
    virtual s32 GetBounds(Box *);
    u8 pad34[0x10];
    Vec3 *verts;
    u8 pad48[0x8];
    s32 count;
    Tri *tris;
    Node *node;
};

extern "C" {
extern void Qsort_132d08(void *, s32, s32, s32 (*)(const void *, const void *));
extern void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
extern void VecMinMax3_13df40(Vec4 *, Vec4 *, Vec4 *, Vec4 *, Vec4 *);
extern void *MemStackNew_14e230(s32, s32);
extern void CollMeshQuadTreeInsert_16c500(Node *, Sub *, Tri *, Vec4 *, s32);
extern s32 CollMeshTriCompareQuadNode_16c4e0(const void *, const void *);
}

#define F(o, T, off) (*(T *)((u8 *)(o) + (off)))

extern "C" void CollMeshBuildQuadTree_16c210(Obj *self, s32 heap) {
    Sub *last;
    s32 m;
    Tri *p;
    Box box;
    Vec4 ctr;
    Vec4 v90;
    Vec4 v80;
    Vec4 va;
    Vec4 vb;
    Vec4 vc;
    Tri *tri;
    f32 size;
    f32 dz;
    f32 step;
    Node *node;
    Sub *sub;
    s32 i;
    Vec3 *verts;
    Vec3 *pa;
    Vec3 *pb;
    Vec3 *pc;
    Node *p0;
    s32 k;
    Sub *n;

    if (self->GetBounds(&box) == 0) {
        return;
    }
    VecAdd_13be20(&ctr, &box.min, &box.max);
    VecScale_13be00(&ctr, &ctr, 0.5f);
    { f32 mz = *(volatile f32 *)&box.max.z; dz = *(volatile f32 *)&box.min.z; dz = dz - mz; }
    { f32 mx = *(volatile f32 *)&box.max.x; size = *(volatile f32 *)&box.min.x; size = size - mx; }
    size = (size > dz) ? size : dz;
    if (size < 100.0f) {
        return;
    }
    if (self->count < 0x30) {
        return;
    }
    step = size / 32.0f;
    if (step < 100.0f) {
        step = 100.0f;
    }
    p0 = (Node *)MemStackNew_14e230(0x10, heap);
    if (p0 != 0) {
        p0->sub = 0;
        p0->heap = heap;
        heap = (s32)p0;
    } else {
        heap = (s32)p0;
    }
    self->node = p0;
    if (heap == 0) {
        return;
    }
    size += 1.0f;
    sub = (Sub *)MemStackNew_14e230(0x30, ((Node *)heap)->heap);
    if (sub != 0) {
        sub->x10 = 0;
        sub->x12 = 0;
        for (k = 0; k < 4; k++) {
            sub->x14[k] = 0;
        }
    }
    ((Node *)heap)->sub = sub;
    if (sub != 0) {
        *(u128 *)&sub->c = *(u128 *)&ctr;
        ((Node *)heap)->x4 = size;
        ((Node *)heap)->x8 = step;
    }
    tri = self->tris;
    for (i = 0; i < self->count; i++, tri++) {
        verts = self->verts;
        pa = &verts[tri->a];
        pb = &verts[tri->b];
        pc = &verts[tri->c];
        va.x = pa->x;
        va.y = pa->y;
        va.z = pa->z;
        vb.x = pb->x;
        vb.y = pb->y;
        vb.z = pb->z;
        vc.x = pc->x;
        vc.y = pc->y;
        vc.z = pc->z;
        va.w = 1.0f;
        vb.w = 1.0f;
        vc.w = 1.0f;
        VecMinMax3_13df40(&v80, &v90, &va, &vb, &vc);
        tri->x8 = 0;
        CollMeshQuadTreeInsert_16c500(self->node, self->node->sub, tri, &v80, 1);
    }
    Qsort_132d08(self->tris, self->count, 0xC, CollMeshTriCompareQuadNode_16c4e0);
    p = self->tris;
    last = 0;
    for (m = 0; m < self->count; m++, p++) {
        n = p->x8;
        if (n != last) {
            n->x10 = m;
            last = n;
            n->x12 = 0;
        }
        n->x12++;
    }
}
