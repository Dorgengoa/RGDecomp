#include "types.h"

struct ObjBase {
    u8 pad0[0x40];
    s32 x40;
    s32 x44;
    s32 x48;
    s32 x4C;
};
class Obj : public ObjBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual s32 draw(s32, s32 *, s32 *, s32);
};

typedef struct Tab {
    s32 x0;
    Obj **objs;
} Tab;

typedef struct Ent {
    s32 id;
    s32 x4;
    s32 idx;
    u32 flags;
    f32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
} Ent;

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    Ent e;
} Node;

typedef struct Desc {
    u8 pad0[8];
    s32 *cnt;
    Tab *tab;
    u8 pad10[0x30];
    s32 filter;
    Node *list;
} Desc;

typedef struct Mesh {
    u8 pad0[0xA];
    u16 xA;
    u8 padC[0xC];
    s16 x18;
    s16 x1A;
} Mesh;

typedef struct Buf {
    u8 pad0[0x28];
    s32 x28;
    s32 x2C;
} Buf;

typedef struct Self {
    u8 pad0[0xD0];
    u8 heap[0x3B90 - 0xD0];
    Mesh *mesh;
    u8 pad3B94[0x3C40 - 0x3B94];
    s32 x3C40;
    u8 pad3C44[0x3CCC - 0x3C44];
    s32 x3CCC;
    u8 pad3CD0[0x3D10 - 0x3CD0];
    s32 c0;
    s32 c1;
    s32 c2;
    s32 c3;
    s32 c4;
} Self;

extern "C" {
extern void DrawCtxAddChangedCallTags_13fd70(Self *, s32 *, s32);
extern void DrawListDepthToSortKey_1409b0(Self *, f32);
extern void DmaPktAddCallTag_141b80(Self *, s32);
extern Buf *DrawListGetCurBuf_142790(Self *);
extern void DmaPktAddMscalCall_145b20(Self *, s32);
extern s32 DrawListWriteTexEnvPacket_148370(Self *, s32, Mesh *);
extern void MemStackAllocQw_14d950(Buf *, s32);
extern void MemStackReturnToOwnerMaybe_14dad0(void *);
extern s32 MemStackHeapAlloc_14db10(void *, s32, s32, s32);
extern void MemStackHeapFree_14dcb0(void *, s32);
extern s32 *MemStackNew_14e1b0(s32, void *);
extern u8 D_00491280[];

}

#pragma opt_dead_assignments off
extern "C" s32 ModelEmitShadowCasterPacketsMaybe_14e780(void *unused, Self *self, Desc *d) {
    s32 bufA[0x80];
    s32 bufB[0x80];
    s32 rec[6];
    Tab *tab;
    Node *node;
    s32 *cntp;
    s32 n;
    s32 flag4;
    s32 *c0;
    s32 *c1;
    s32 *c2;
    s32 *c3;
    s32 *c4;
    Buf *buf;
    s32 hnd;
    s32 cur;
    void *heap;
    s32 *a;
    s32 *b;
    Mesh *mesh;
    s32 ofs;
    s32 filter;
    u8 *row;
    Ent *e;
    Obj *obj;
    u32 fl;
    s32 f3;
    s32 s160;
    s32 s150;
    s32 base;
    s32 i;
    s32 p;
    u8 *t;
    s32 k;

    tab = d->tab;
    node = d->list;
    cntp = d->cnt;
    if (node == 0) {
        return 0;
    }
    if (cntp == 0) {
        return 0;
    }
    n = *cntp;
    flag4 = 0;
    if (self->x3CCC != 0) {
        flag4 = 4;
    }
    c0 = &self->c0;
    c1 = &self->c1;
    c2 = &self->c2;
    c3 = &self->c3;
    c4 = &self->c4;
    buf = DrawListGetCurBuf_142790(self);
    if (buf == 0) {
        return 0;
    }
    heap = self->heap;
    hnd = 0;
    base = buf->x28 + buf->x2C * 16;
    cur = base;
    if (n >= 0x80) {
        hnd = MemStackHeapAlloc_14db10(heap, 2, 0, 0x40);
        a = MemStackNew_14e1b0(n * 4, heap);
        b = MemStackNew_14e1b0(n * 4, heap);
        MemStackReturnToOwnerMaybe_14dad0(heap);
        if (a == 0 || b == 0) {
            MemStackHeapFree_14dcb0(heap, hnd);
            return 0;
        }
    } else {
        a = bufA;
        b = bufB;
    }
    mesh = self->mesh;
    ofs = 0;
    if (mesh != 0) {
        ofs = base;
        cur += DrawListWriteTexEnvPacket_148370(self, base, mesh) * 16;
    }
    if (ofs == 0 || mesh == 0) {
        node = 0;
    }
    filter = d->filter;
    row = D_00491280 + self->x3C40 * 0xC0;
    for (; node != 0; node = node->next) {
        e = &node->e;
        if (filter != 0 && e->id != filter) {
            continue;
        }
        if (e->x14 == 0) {
            continue;
        }
        if (e->x18 == 0) {
            continue;
        }
        obj = tab->objs[e->idx];
        if (obj == 0) {
            continue;
        }
        *c0 += 1;
        *c1 += obj->x40;
        *c2 += obj->x44;
        *c3 += obj->x48;
        *c4 += obj->x4C;
        fl = e->flags;
        f3 = fl & 3;
        s160 = 0;
        if (fl & 4) {
            s160 = 2;
        }
        s150 = 0;
        if (fl & 8) {
            s150 = 2;
        }
        if (fl & 0x10) {
            DrawListDepthToSortKey_1409b0(self, e->x10);
        }
        DmaPktAddCallTag_141b80(self, e->x14);
        DmaPktAddCallTag_141b80(self, e->x18);
        DmaPktAddCallTag_141b80(self, e->x1C);
        cur += obj->draw(cur, b, a, n) * 16;
        for (i = 0; i < n; i++) {
            if (b[i] < 0) {
                break;
            }
            p = a[i];
            if (p != 0) {
                s32 i18;
                s32 i1A;
                s32 off;
                off = mesh->xA;
                i18 = s160 + mesh->x18;
                i1A = s150 + mesh->x1A;
                i1A |= flag4;
                t = row + off * 16;
                rec[0] = *(s32 *)(t + 0);
                rec[1] = *(s32 *)(t + 4);
                rec[2] = *(s32 *)(t + 8);
                rec[3] = (*(s32 **)(t + 0x300))[f3];
                rec[4] = (*(s32 **)(t + 0x304))[i18];
                rec[5] = (*(s32 **)(t + 0x308))[i1A];
                DrawCtxAddChangedCallTags_13fd70(self, rec, 6);
                DmaPktAddCallTag_141b80(self, ofs);
                DmaPktAddMscalCall_145b20(self, p);
            }
        }
    }
    if (hnd != 0) {
        MemStackHeapFree_14dcb0(heap, hnd);
    }
    k = (cur - base) / 16;
    MemStackAllocQw_14d950(buf, k);
    return k;
}
