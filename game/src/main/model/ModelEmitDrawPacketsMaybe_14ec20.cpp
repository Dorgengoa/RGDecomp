#include "types.h"
typedef rg_u128 u128;

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
} Ent;

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
    u8 padC[0xC];
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
    VC_VPTR_MEMBER;
    
    
    
    s32 v18(u128 * a0, s32 * a1, s32 * a2, s32 a3) { return VCM(s32, (void *, u128 *, s32 *, s32 *, s32), 0x18, a0, a1, a2, a3); }
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

extern "C" {
void DrawCtxAddChangedCallTags_13fd70(Ctx *, s32 *, s32);
s32 DrawListDepthToSortKey_1409b0(Ctx *, f32);
void DmaPktAddCallTag_141b80(Ctx *, s32);
Pkt *DrawListGetCurBuf_142790(Ctx *);
void DmaPktAddMscalCall_145b20(Ctx *, s32);
s32 DrawListWriteTexEnvPacket_148370(Ctx *, u128 *, Mesh *);
s32 MemStackAllocQw_14d950(Pkt *, s32);
void MemStackReturnToOwnerMaybe_14dad0(void *);
s32 MemStackHeapAlloc_14db10(void *, s32, s32, s32);
void MemStackHeapFree_14dcb0(void *, s32);
s32 *MemStackNew_14e1b0(u32, void *);
extern Row D_00491280[];

#pragma opt_dead_assignments off
s32 ModelEmitDrawPacketsMaybe_14ec20(s32 unused, Ctx *o, Req *rq) {
    s32 bufA[0x80] __attribute__((aligned(16)));
    s32 bufB[0x80] __attribute__((aligned(16)));
    s32 info[6] __attribute__((aligned(16)));
    s32 cnt;
    s32 flag;
    Pkt *pk;
    s32 mark;
    s32 *A;
    s32 *B;
    s32 s170;
    s32 s160;
    s32 w;
    Set *set;
    Node *e;
    Tbl *tbl;
    s32 *p0;
    s32 *p1;
    s32 *p2;
    s32 *p3;
    s32 *p4;
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
    flag = 0;
    if (o->f3CCC != 0) {
        flag = 4;
    }
    p0 = &o->n0;
    p1 = &o->n1;
    p2 = &o->n2;
    p3 = &o->n3;
    p4 = &o->n4;
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
        s170 = 0;
        *p0 += 1;
        *p1 += m->f40;
        *p2 += m->f44;
        *p3 += m->f48;
        *p4 += m->f4C;
        fl = d->flags;
        lod = fl & 3;
        if (fl & 4) {
            s170 = 2;
        }
        s160 = 0;
        if (fl & 8) {
            s160 = 2;
        }
        if (fl & 0x10) {
            DrawListDepthToSortKey_1409b0(o, d->f10);
        }
        DmaPktAddCallTag_141b80(o, d->f14);
        DmaPktAddCallTag_141b80(o, d->f18);
        DmaPktAddCallTag_141b80(o, d->f1C);
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
            off = t->fA;
            k4 = s170 + t->f18;
            k5 = s160 + t->f1A;
            k5 |= flag;
            ent = (TabE *)(tab + off * 16);
            info[0] = ent->f0;
            info[1] = ent->f4;
            info[2] = ent->f8;
            info[3] = ent->f300[lod];
            info[4] = ent->f304[k4];
            info[5] = ent->f308[k5];
            DrawCtxAddChangedCallTags_13fd70(o, info, 6);
            DmaPktAddCallTag_141b80(o, v);
            DmaPktAddMscalCall_145b20(o, w);
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
