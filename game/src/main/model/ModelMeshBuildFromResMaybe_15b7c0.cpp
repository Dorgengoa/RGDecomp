#include "types.h"
#pragma divbyzerocheck on
#pragma optimization_level 3

typedef rg_u128 u128;

typedef union {
    u128 q;
    f32 f[4];
} Vec4;

typedef struct Heap Heap;

typedef struct {
    u8 pad0[0x6C];
    u16 f6C;
} Hdr0;

typedef struct {
    Hdr0 *p0;
    u8 pad4[0xC];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
} Src;

typedef struct {
    s32 n0;
    void *p0;
    s32 n1;
    void *p1;
    s32 n2;
    void *p2;
    s32 n3;
    void *p3;
    u8 pad20[4];
    u8 *w8;             /* 0x24 */
    s16 *idx;           /* 0x28 */
    u8 pad2C[4];
    Vec4 v30;
    Vec4 v40;
    Vec4 v50;
    f32 f60;
} Hdr;

typedef struct {
    s32 key;
    void *p4;
    void *p8;
    void *pC;
} Ent;

typedef struct Node {
    struct Node *next;
    u16 id;
    u16 n;
    u8 cnt;
    u8 pad9[3];
    Ent *items;
    void *data;
} Node;

typedef struct Grp {
    struct Grp *next;
    void *data;
    s32 n;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
} Grp;

typedef struct Item {
    struct Item *next;
    s32 id;
    s32 n;
    s32 fC;
    s32 f10;
    struct Item *f14;
    Grp *grp;
    Grp *e1C;
    Grp *e20;
    Grp *e24;
} Item;

typedef struct {
    struct Item *pad0;
    Item *head;
} Slot;

typedef struct {
    s32 f0;
    s32 bits0;
    s32 bits1;
    s32 bits2;
    u8 f10[0x10];
    u8 f20[0x10];
    u8 f30[0x10];
    u8 f40[0x10];
    s32 n0;
    void *p0;
    s32 n1;
    void *p1;
    s32 n2;
    void *p2;
    s32 n3;
    void *p3;
    void *wt;           /* 0x70 */
    Grp *g74;
    Grp *g78;
    Grp *g7C;
    Grp *g80;
} Data;

typedef struct {
    u8 b[4];
    u8 w[4];
    s32 n;
} Wt;

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    Vec4 v10;
    Vec4 v20;
    Vec4 v30;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    u8 pad50[0x10];
    Data d;             /* 0x60 */
    u8 padE4[0x1C];
    Vec4 v100;
    Vec4 v110;
    f32 f120;
    s32 f124;
    s32 nb;             /* 0x128 */
    s32 *bones;         /* 0x12C */
} Obj;

extern "C" {
void *memcpy(void *, const void *, u32);
void *ConstructNewArray_100710(void *, s32, s32, s32, s32);
void ModelResGetUvScale_14cbd0(Src *, u8 *);
Hdr0 *ArrayGetChecked_14cb80(Src *, s32);
void ModelResGetNormalScale_14cc30(Src *, u8 *);
void ModelResGetPosOffsetMaybe_14cc90(Src *, u8 *);
void ModelResGetPosScale_14ccb0(Src *, u8 *);
s32 ModelResGetWeightFormat_14cd10(Src *);
s32 ModelResGetUvFormat_14cd30(Src *);
s32 ModelResGetNormalFormat_14cd50(Src *);
s32 ModelResGetPosFormat_14cd70(Src *);
s32 ModelResGetSkinInfluenceCount_14cdb0(Src *);
Node *ModelResGetPrimGroupList_14ce20(Src *);
Hdr *ModelResGetVertexBufMaybe_14ce60(Src *);
void *MemStackAllocQw_14d950(Heap *, s32);
void *MemStackNew_14e1b0(s32, Heap *);
Grp *MemStackNew_14e230(s32, Heap *);
Slot *ModelMeshGroupFindOrAddMaybe_15c680(Obj *, s32, s32, Heap *);
void ModelResCalcPrimCountMaybe_15c780(Obj *, s32, s32 *);
}

static inline s32 Valid(Src *s) {
    return s->p0 != 0 && s->p0->f6C == 0;
}

static inline void *Dup(Heap *heap, void *src, s32 bits, s32 count) {
    void *p;
    s32 size;
    s32 n;

    if (count <= 0) return 0;
    size = count * bits / 8;
    n = size / 16;
    if (size % 16 != 0) n++;
    p = MemStackAllocQw_14d950(heap, n);
    if (p == 0) return 0;
    memcpy(p, src, size);
    return p;
}

static inline Grp *NewGrp(Heap *heap, Grp **head) {
    Grp *g;
    Grp *t;

    g = MemStackNew_14e230(0x1C, heap);
    if (g == 0) return 0;
    g->next = 0;
    g->n = 0;
    g->fC = 0;
    g->f10 = 0;
    g->data = 0;
    g->f14 = 0;
    g->f18 = 0;
    if (*head != 0) {
        for (t = *head; t->next != 0; t = t->next) {
        }
        t->next = g;
    } else {
        *head = g;
    }
    return g;
}

static inline Grp *Find(Grp *e, void *key) {
    if (e == 0) return 0;
    while (e->next != 0) {
        if (e->data == key) return e;
        e = e->next;
    }
    return 0;
}

#define DUPR(r, heap, src, bits, count)     if ((count) <= 0) {         r = 0;     } else {         dsz = (count) * (bits) / 8;         dn = dsz / 16;         if (dsz % 16 != 0) dn++;         dp = MemStackAllocQw_14d950(heap, dn);         if (dp == 0) {             r = 0;         } else {             memcpy(dp, src, dsz);             r = dp;         }     }

extern "C" s32 ModelMeshBuildFromResMaybe_15b7c0(Obj *o, Src *src, Heap *heap, s32 copy) {
    s32 tmp;
    Data *d;
    Hdr *hdr;
    Node *node;
    s32 j;
    Ent *items;
    s32 cnt;
    Grp *e;
    Item *arr;
    Item *it;
    Item *t;
    Hdr0 *m;
    Slot *sl;
    Wt *wt;
    s32 k;
    Wt *q;
    u8 *w8;
    s16 *idx;
    s32 fmt;
    Grp *g;
    s32 id;
    s32 n;
    s32 ky;
    s32 v;
    void *key1;
    void *key2;
    void *key3;
    void *r1;
    void *r2;
    void *r3;
    u16 *w16;
    s32 kind;
    s32 bytes;
    s32 lim;
    s32 c;
    s32 b;
    s32 wgt;
    s32 sum;
    s32 x;
    s32 i;
    s32 sz;
    s32 nb;
    s32 half;
    s32 dsz;
    s32 dn;
    void *dp;

    if (src == 0 || !Valid(src)) return 0;
    d = &o->d;
    hdr = ModelResGetVertexBufMaybe_14ce60(src);
    if (hdr == 0) return 0;
    node = ModelResGetPrimGroupList_14ce20(src);
    if (node == 0) return 0;
    o->f40 = src->f10;
    o->f44 = src->f14;
    o->f48 = src->f18;
    o->f4C = src->f1C;
    ModelResGetPosScale_14ccb0(src, d->f10);
    ModelResGetPosOffsetMaybe_14cc90(src, d->f20);
    ModelResGetNormalScale_14cc30(src, d->f30);
    ModelResGetUvScale_14cbd0(src, d->f40);
    d->bits0 = ModelResGetPosFormat_14cd70(src);
    d->bits1 = ModelResGetNormalFormat_14cd50(src);
    d->bits2 = ModelResGetUvFormat_14cd30(src);
    fmt = ModelResGetWeightFormat_14cd10(src);
    d->n0 = hdr->n0;
    d->n1 = hdr->n1;
    d->n2 = hdr->n2;
    d->n3 = hdr->n3;
    if (copy != 0) {
        d->p0 = Dup(heap, hdr->p0, d->bits0, d->n0 * 3);
        d->p1 = Dup(heap, hdr->p1, d->bits1, d->n1 * 3);
        d->p2 = Dup(heap, hdr->p2, d->bits2, d->n2 * 2);
        d->p3 = Dup(heap, hdr->p3, 8, d->n3 * 4);
    } else {
        d->p0 = hdr->p0;
        d->p1 = hdr->p1;
        d->p2 = hdr->p2;
        d->p3 = hdr->p3;
    }
    o->v20.q = hdr->v40.q;
    o->v20.f[3] = 1.0f;
    o->v30.q = hdr->v30.q;
    o->v30.f[3] = 1.0f;
    o->v100.q = o->v20.q;
    o->v110.q = o->v30.q;
    o->f120 = hdr->f60;
    o->v10.q = hdr->v50.q;
    for (; node != 0; node = node->next) {
        items = node->items;
        cnt = node->cnt;
        n = node->n;
        id = node->id;
        if (items == 0 || cnt == 0) continue;
        tmp = 0;
        ModelResCalcPrimCountMaybe_15c780(o, id, &tmp);
        g = NewGrp(heap, &d->g74);
        if (g == 0) break;
        if (copy != 0) {
            g->data = Dup(heap, node->data, 16, n);
        } else {
            g->data = node->data;
        }
        g->n = n;
        arr = (Item *)ConstructNewArray_100710(MemStackNew_14e1b0(cnt * 40 + 16, heap), 0, 0, 40, cnt);
        for (j = 0; j < cnt; j++, items++) {
            it = &arr[j];
            it->next = 0;
            it->id = 0;
            it->n = 0;
            it->f14 = 0;
            it->f10 = 0;
            it->fC = 0;
            it->grp = 0;
            it->e1C = 0;
            it->e20 = 0;
            it->e24 = 0;
            it->id = id;
            it->n = n;
            it->grp = g;
            ky = items->key;
            it->f14 = 0;
            m = ArrayGetChecked_14cb80(src, ky);
            v = items->key + 10;
            if (m != 0) {
                switch (*(s32 *)((u8 *)m + 0x40)) {
                case 2:
                case 3:
                case 9:
                case 11:
                    v += 10000;
                    if (j > 0) it->f14 = arr;
                    break;
                }
            }
            key1 = items->p8;
            if (key1 != 0) {
                e = Find(d->g78, key1);
                if (e == 0) e = NewGrp(heap, &d->g78);
                if (e != 0) {
                    if (copy != 0) {
                        DUPR(r1, heap, key1, 16, n);
                        e->data = r1;
                    } else {
                        e->data = key1;
                    }
                    e->n = n;
                }
                it->e1C = e;
            }
            key2 = items->p4;
            if (key2 != 0) {
                e = Find(d->g7C, key2);
                if (e == 0) e = NewGrp(heap, &d->g7C);
                if (e != 0) {
                    if (copy != 0) {
                        DUPR(r2, heap, key2, 16, n);
                        e->data = r2;
                    } else {
                        e->data = key2;
                    }
                    e->n = n;
                }
                it->e20 = e;
            }
            key3 = items->pC;
            if (key3 != 0) {
                e = Find(d->g80, key3);
                if (e == 0) e = NewGrp(heap, &d->g80);
                if (e != 0) {
                    if (copy != 0) {
                        DUPR(r3, heap, key3, 16, n);
                        e->data = r3;
                    } else {
                        e->data = key3;
                    }
                    e->n = n;
                }
                it->e24 = e;
            }
            sl = ModelMeshGroupFindOrAddMaybe_15c680(o, ky, v, heap);
            if (sl == 0) break;
            if (sl->head == 0) {
                sl->head = it;
            } else {
                for (t = sl->head; t->next != 0; t = t->next) {
                }
                t->next = it;
            }
        }
    }
    wt = 0;
    n = ModelResGetSkinInfluenceCount_14cdb0(src);
    if (n > 0) {
        o->nb = 0;
        o->bones = (s32 *)MemStackNew_14e1b0(0x90, heap);
        cnt = d->n0;
        wt = (Wt *)MemStackNew_14e1b0(cnt * 12, heap);
        idx = hdr->idx;
        q = wt;
        lim = n;
        w8 = hdr->w8;
        w16 = (u16 *)w8;
        if (n > 4) lim = 4;
        for (i = 0; i < cnt; i++, q++, idx += n, w8 += n, w16 += n) {
            *(s32 *)&q->b[0] = 0;
            *(s32 *)&q->w[0] = 0;
            c = 0;
            q->n = 0;
            for (k = 0; k < lim; k++) {
                b = idx[k];
                if (b < 0) continue;
                if (fmt == 8) {
                    wgt = (w8[k] << 15) / 100;
                } else {
                    wgt = w16[k];
                }
                if (wgt == 0) continue;
                wgt = wgt / 128;
                if (wgt > 255) wgt = 255;
                if (i == 75 && k == 0) wgt++;
                nb = o->nb;
                for (x = 0; x < nb; x++) {
                    if (o->bones[x] == b) break;
                }
                if (x == 36) continue;
                if (x == nb) {
                    o->bones[o->nb++] = b;
                }
                q->b[k] = -x * 2 - 2;
                c++;
                q->w[k] = wgt;
            }
            q->n = c;
            sum = q->w[0] + q->w[1] + q->w[2] + q->w[3];
            if (sum != 255) q->w[0] += 255 - sum;
        }
        if (o->bones != 0 && o->nb != 0) {
            sz = o->nb * 4;
            half = sz / 2;
            if (sz % 2 != 0) half++;
            o->f0 = 0x8C;
            o->f4 = 0x17C - half;
            o->f8 = o->f4 / 2;
            o->fC = o->f4 / 2;
            o->f124 = 900 - sz;
        }
    }
    d->wt = wt;
    return 1;
}
