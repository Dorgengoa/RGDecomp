#include "types.h"

typedef struct Elem {
    u8 pad[0x38];
} Elem;

typedef struct Query {
    s32 a;
    s32 b;
    Elem arr[64];
} Query;

typedef struct Iter {
    s32 a;
    s32 b;
} Iter;

typedef struct Node {
    u8 pad00[8];
    s16 h8;
    u8 pad0A[2];
    s16 hC;
    u8 pad0E[0x28 - 0xE];
    s16 h28;
    s16 h2A;
    u8 pad2C[4];
    s32 w30;
    s32 w34;
    u8 pad38[8];
    s32 w40;
} Node;

typedef struct Ent {
    u8 pad[0x98];
} Ent;

typedef struct Tbl {
    u8 pad[0xC];
    Ent *ents;
} Tbl;

typedef struct Scene {
    u8 pad[0x78];
    Tbl *tbl;
} Scene;

typedef struct Rec {
    s16 *id;
    u8 pad04[0xC];
    s16 h10;
} Rec;

typedef struct Self {
    u8 pad0[8];
    Scene *scene;
    u8 padC[4];
    s32 w10;
} Self;

s32 VariantIsZero_36ed10(s32);
void VariantInit_36ff00(Elem *);
Node *IterNext_370040(Iter *);
void IterInit_370170(Iter *, void *);
s32 StateFlag2Test_3cc860(s32, s16);
s32 ScriptExecOpStream_3dffa0(Query *, s16, s32, s32);
void VariantPoolReset_3e01f0(Query *);
Rec *HandleEntryGet_3f24b0(Scene *, s32);
extern const s32 D_004644A0[4];
extern const s32 D_004644A8[4];

static inline Ent *getEnt(Tbl *t, s32 k, s32 lim) {
    Ent *e;
    if (k >= 0) {
        if (k >= lim) {
            e = 0;
        } else {
            e = &t->ents[k];
        }
    } else {
        e = 0;
    }
    return e;
}

s32 TreasureBoxParamRefreshCondsMaybe_3eca40(Self *self, s32 id) {
    Iter it[2];
    Query q1;
    Query q2;
    s32 n;
    s32 lim;
    s32 i;
    Rec *r;
    s16 k;
    Ent *e;
    Node *o;
    Elem *p;
    u8 *b;
    s32 res;

    if (self->scene == 0) {
        return 0;
    }
    for (i = 0; i < D_004644A0[0]; i++) {
        r = HandleEntryGet_3f24b0(self->scene, i);
        if (r == 0) {
            continue;
        }
        if (r->id == 0) {
            continue;
        }
        if (id >= 0 && *r->id != id) {
            continue;
        }
        e = getEnt(self->scene->tbl, r->h10, D_004644A8[0]);
        if (e == 0) {
            continue;
        }
        b = (u8 *)e;
        if (b != 0) {
            b += 0x88;
        }
        IterInit_370170(&it[1], b);
        while ((o = IterNext_370040(&it[1])) != 0) {
            o->w40 = 6;
            if (o->hC == 0xB) {
                k = o->h8;
                if (k >= 0 && (StateFlag2Test_3cc860(self->w10, k) & 0xFF)) {
                    o->w40 &= ~2;
                }
            }
            if ((o->w40 & 2) && o->h28 > 0 && o->w30 != 0) {
                p = q1.arr;
                do {
                    VariantInit_36ff00(p);
                    p++;
                } while (p < q1.arr + 64);
                VariantPoolReset_3e01f0(&q1);
                res = ScriptExecOpStream_3dffa0(&q1, o->h28, o->w30, 0);
                if (res != 0 && VariantIsZero_36ed10(res) != 0) {
                    o->w40 &= ~2;
                }
            }
            if ((o->w40 & 2) && o->h2A > 0 && o->w34 != 0) {
                p = q2.arr;
                do {
                    VariantInit_36ff00(p);
                    p++;
                } while (p < q2.arr + 64);
                VariantPoolReset_3e01f0(&q2);
                res = ScriptExecOpStream_3dffa0(&q2, o->h2A, o->w34, 0);
                if (res != 0 && VariantIsZero_36ed10(res) != 0) {
                    o->w40 &= ~2;
                }
            }
        }
    }
    return 1;
}
