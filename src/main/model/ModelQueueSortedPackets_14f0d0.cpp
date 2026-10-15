#include "types.h"
typedef unsigned __int128 u128;

typedef struct {
    u8 pad0[0xD0];
    u8 heap[0x3C40 - 0xD0];     /* 0xD0 */
    s32 f3C40;
    u8 pad3C44[0x3CCC - 0x3C44];
    s32 f3CCC;
    u8 pad3CD0[0x3D10 - 0x3CD0];
    s32 n0;                     /* 0x3D10 */
    s32 n1;
    s32 n2;
    s32 n3;
    s32 n4;
} Ctx;

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    u8 padC[0x300 - 0xC];
    s32 *f300;
    s32 *f304;
    s32 *f308;
} TabE;

typedef struct {
    u8 b[0xC0];
} Row;

typedef struct {
    u8 pad0[0xA];
    u16 fA;
    s32 fC;
    u8 pad10[8];
    s16 f18;
    s16 f1A;
} Mesh;

typedef struct {
    s32 cnt;
    Mesh **meshes;
    s32 *addrs;
} Tbl;

class Model {
public:
    u8 pad0[0x40];
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual s32 v18(u128 *, s32 *, s32 *, s32);
};

typedef struct {
    u8 pad0[4];
    Model **models;
} Set;

typedef struct {
    s32 key;
    s32 f4;
    s32 idx;
    s32 flags;
    f32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
} Part;

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    Part part;          /* 0x10 */
} Node;

typedef struct {
    u8 pad0[8];
    Tbl *tbl;           /* 0x08 */
    Set *set;           /* 0x0C */
    u8 pad10[0x30];
    s32 key;            /* 0x40 */
    Node *list;         /* 0x44 */
} Req;

typedef struct {
    u8 pad0[0x28];
    u128 *buf;
    s32 used;
} Pkt;

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 *hdr;
    s32 f14;
    s32 *pkt;
    s32 addr;
    s32 w;
    s32 pad[3];
} Rec;

#pragma opt_dead_assignments off
extern "C" {
s32 DrawListDepthToSortKey_1409b0(Ctx *, f32);
void DrawListAddNode_140a10(Ctx *, Rec *, s32);
Pkt *DrawListGetCurBuf_142790(Ctx *);
s32 LightStateGetPacket_1428f0(Ctx *, s32 *);
s32 DrawListEnsureViewPacket_148240(Ctx *);
s32 DrawListWriteTexEnvPacket_148370(Ctx *, u128 *, Mesh *);
s32 MemStackAllocQw_14d950(Pkt *, s32);
void MemStackReturnToOwnerMaybe_14dad0(void *);
s32 MemStackHeapAlloc_14db10(void *, s32, s32, s32);
void MemStackHeapFree_14dcb0(void *, s32);
s32 *MemStackNew_14e1b0(u32, void *);
extern Row D_00491280[];

s32 ModelQueueSortedPackets_14f0d0(s32 unused, Ctx *o, Req *rq) {
    s32 cnt;
    s32 flag;
    Pkt *pk;
    s32 mark;
    s32 *A;
    s32 *B;
    s32 out;
    Rec rec;
    s32 bufA[0x80];
    s32 bufB[0x80];
    s32 s1A0;
    s32 s190;
    s32 r0;
    s32 w;
    Set *set;
    Node *e;
    Tbl *tbl;
    s32 *p0;
    s32 *p1;
    s32 *p2;
    s32 *p3;
    s32 *p4;
    s32 r110;
    s32 r100;
    u128 *base;
    u128 *cur;
    void *heap;
    s32 key;
    u8 *tab;
    Part *d;
    Model *m;
    s32 fl;
    s32 lod;
    s32 i;
    s32 j;
    Mesh *t;
    s32 v;
    TabE *ent;
    s32 n;
    s32 *q;
    s32 k4;
    s32 k5;
    s32 off;

    set = rq->set;
    e = rq->list;
    tbl = rq->tbl;
    if (e == 0) {
        return 0;
    }
    if (tbl == 0) {
        return 0;
    }
    cnt = tbl->cnt;
    rec.fC = 5;
    rec.f14 = 6;
    flag = 0;
    if (o->f3CCC != 0) {
        flag = 4;
    }
    p0 = &o->n0;
    p1 = &o->n1;
    p2 = &o->n2;
    p3 = &o->n3;
    p4 = &o->n4;
    r110 = LightStateGetPacket_1428f0(o, &out);
    r100 = DrawListEnsureViewPacket_148240(o);
    pk = DrawListGetCurBuf_142790(o);
    if (pk == 0) {
        return 0;
    }
    heap = o->heap;
    mark = 0;
    base = pk->buf + pk->used;
    cur = base;
    if (cnt >= 0x80) {
        mark = MemStackHeapAlloc_14db10(heap, 2, 0, 0x40);
        A = MemStackNew_14e1b0(cnt * 4, heap);
        B = MemStackNew_14e1b0(cnt * 4, heap);
        MemStackReturnToOwnerMaybe_14dad0(heap);
        if (A == 0 || B == 0) {
            MemStackHeapFree_14dcb0(heap, mark);
            return 0;
        }
    } else {
        A = bufA;
        B = bufB;
    }
    key = rq->key;
    tab = D_00491280[o->f3C40].b;
    for (; e != 0; e = e->next) {
        d = &e->part;
        if (key != 0 && d->key != key) {
            continue;
        }
        if (d->f14 == 0) {
            continue;
        }
        if (d->f18 == 0) {
            continue;
        }
        m = set->models[d->idx];
        if (m == 0) {
            continue;
        }
        s1A0 = 0;
        *p0 += 1;
        *p1 += m->f40;
        *p2 += m->f44;
        *p3 += m->f48;
        *p4 += m->f4C;
        fl = d->flags;
        lod = fl & 3;
        if (fl & 4) {
            s1A0 = 2;
        }
        s190 = 0;
        if (fl & 8) {
            s190 = 2;
        }
        if (fl & 0x10) {
            r0 = DrawListDepthToSortKey_1409b0(o, d->f10);
        } else {
            r0 = 0;
        }
        rec.hdr = (s32 *)cur;
        rec.hdr[0] = r100;
        cur += 2;
        rec.hdr[1] = r110;
        rec.hdr[2] = d->f14;
        rec.hdr[3] = d->f18;
        rec.hdr[4] = d->f1C;
        cur += m->v18(cur, B, A, cnt);
        for (i = 0; i < cnt; i++) {
            j = B[i];
            if (j < 0) {
                break;
            }
            w = A[i];
            if (w == 0) {
                continue;
            }
            t = tbl->meshes[j];
            if (t == 0) {
                continue;
            }
            v = tbl->addrs[j];
            if (v == 0) {
                v = (s32)cur;
                cur += DrawListWriteTexEnvPacket_148370(o, cur, t);
                tbl->addrs[j] = v;
            }
            q = (s32 *)cur;
            off = t->fA;
            cur += 2;
            k4 = s1A0 + t->f18;
            ent = (TabE *)(tab + off * 16);
            k5 = s190 + t->f1A;
            k5 |= flag;
            q[0] = ent->f0;
            q[1] = ent->f4;
            q[2] = ent->f8;
            q[3] = ent->f300[lod];
            q[4] = ent->f304[k4];
            q[5] = ent->f308[k5];
            rec.addr = v;
            rec.pkt = q;
            rec.w = w;
            rec.f0 = t->fC;
            DrawListAddNode_140a10(o, &rec, r0);
        }
    }
    if (mark != 0) {
        MemStackHeapFree_14dcb0(heap, mark);
    }
    n = cur - base;
    MemStackAllocQw_14d950(pk, n);
    return n;
}
}
