#include "types.h"

struct Vec4 { f32 x, y, z, w; };

struct Bone {
    u8 pad0[0x4];
    s16 unk4;
    u16 unk6;
    u8 pad8[0x2C];
    f32 p[3];
    f32 v[3];
    u8 pad4C[0x4];
};

struct Node {
    f32 f0;
    f32 f4;
    s16 i8;
    u16 fA;
};

struct Link {
    f32 f0;
    f32 f4;
    s16 i8;
    s16 iA;
    f32 fC;
    f32 f10;
};

struct Elem {
    u8 pad0[0x4];
    s32 unk4;
    u8 pad8[0x4];
    u8 unkC;
    u8 padD[0x23];
};

struct List {
    u8 pad0[0x4];
    s32 unk4;
    u8 pad8[0xC];
    s32 count;
    Elem *data;
};

class Factory {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual List *create(s32 n);
};

struct Self {
    u8 pad0[0x7C];
    s32 unk7C;
    u8 pad80[0x100];
    Bone bones[0x10];
    s16 unk680;
    u8 pad682[0x2];
    Node nodes[0x10];
    Link links[0x10];
    s16 unk884;
    s16 unk886;
};

extern "C" {
void VecLerp_1cbb20(Vec4 *, Vec4 *, Vec4 *, f32);
void HitShapeSetCapsule_3171a0(Elem *, Vec4 *, Vec4 *, s32, f32);
void HitShapeSetSphere_3171d0(Elem *, Vec4 *, s32, f32);
s32 NodeRefFindFrameIndex_319240(Bone *);
}

static inline Elem *elemAt(List *l, s32 i) {
    if (i < 0 || i >= l->count) return 0;
    return &l->data[i];
}

extern "C" List *NodeRefObjBuildHitShapeList_318650(Self *self, Factory *fac) {
    Vec4 p;
    Vec4 q;
    Vec4 c;
    Vec4 a;
    Vec4 r2;
    Vec4 r1;
    List *list;
    s32 k;
    s32 i;
    s32 j;
    Node *n;
    Link *l;
    Elem *e;
    Bone *b;
    Bone *b0;
    Bone *b1;
    u16 fl;

    if (self->bones == 0 || self->unk680 <= 0) {
        return 0;
    }
    list = fac->create(self->unk884 + self->unk886);
    if (list == 0) {
        return 0;
    }
    k = 0;
    n = self->nodes;
    for (i = 0; i < self->unk884; i++, n++) {
        if (!(n->f0 <= 0.0f)) continue;
        e = elemAt(list, k);
        if (e == 0) break;
        b = &self->bones[n->i8];
        fl = b->unk6;
        if (!(fl & 1) && !(fl & 2)) continue;
        if (n->fA & 1) {
            if ((fl & 1) && (fl & 2)) {
                p.x = b->p[0];
                p.y = b->p[1];
                p.z = b->p[2];
                p.w = 1.0f;
                q.x = b->v[0];
                q.y = b->v[1];
                q.z = b->v[2];
                q.w = 1.0f;
                HitShapeSetCapsule_3171a0(e, &p, &q, NodeRefFindFrameIndex_319240(b), n->f4);
                k++;
                e->unk4 = b->unk4;
                e->unkC = (n->fA & 2) != 0;
                continue;
            }
            if (fl & 1) {
                p.x = b->p[0];
                p.y = b->p[1];
                p.z = b->p[2];
                p.w = 1.0f;
            } else {
                p.x = b->v[0];
                p.y = b->v[1];
                p.z = b->v[2];
                p.w = 1.0f;
            }
        } else {
            if (!(fl & 1)) continue;
            p.x = b->p[0];
            p.y = b->p[1];
            p.z = b->p[2];
            p.w = 1.0f;
        }
        HitShapeSetSphere_3171d0(e, &p, NodeRefFindFrameIndex_319240(b), n->f4);
        k++;
        e->unk4 = b->unk4;
        e->unkC = (n->fA & 2) != 0;
    }
    l = self->links;
    for (j = 0; j < self->unk886; j++, l++) {
        if (!(l->f0 <= 0.0f)) continue;
        e = elemAt(list, k);
        if (e == 0) break;
        b0 = &self->bones[l->i8];
        b1 = &self->bones[l->iA];
        if (!(b0->unk6 & 1)) continue;
        if (!(b1->unk6 & 1)) continue;
        a.x = b0->p[0];
        a.y = b0->p[1];
        a.z = b0->p[2];
        a.w = 1.0f;
        c.x = b1->p[0];
        c.y = b1->p[1];
        c.z = b1->p[2];
        c.w = 1.0f;
        VecLerp_1cbb20(&r1, &c, &a, l->fC);
        VecLerp_1cbb20(&r2, &c, &a, l->f10);
        HitShapeSetCapsule_3171a0(e, &r1, &r2, -1, l->f4);
        { s32 o = b1->unk4; s32 m = b0->unk4; e->unk4 = (o < m) ? m : o; }
        k++;
    }
    list->unk4 = self->unk7C;
    list->count = k;
    return list;
}
