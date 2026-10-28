/* rgp:protos */
#define RGP_SELF_MapObjParamRefreshCondsMaybe_3ed0a0 1
#define RGP_SELF_getEnt 1
#include "port/game_protos.h"
#line 1
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

typedef struct Node { u8 pad[0xC]; s16 h28; u8 pE[2]; s32 w30; s16 h2A; u8 p16[2]; s32 w34; s32 w40; } Node;
typedef struct Ent {u8 pad[0xB4];} Ent;
typedef struct Tbl {u8 pad[0x4C];Ent *ents;} Tbl;
typedef struct Rec {s16 *id;s32 pad4;s16 h10;u8 padA[0x12];} Rec;
typedef struct Scene {u8 pad[0xC];Rec *recs;u8 pad10[0x24];Tbl *tbl;} Scene;
typedef struct Self {
    u8 pad0[8];
    Scene *scene;
    u8 padC[4];
    s32 w10;
} Self;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004644A0[4];
extern s32 D_004644A8[4];

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

s32 MapObjParamRefreshCondsMaybe_3ed0a0(Self *self, s32 id) {
    Iter it[2] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Query)]; char m1[0xe0d]; })];
    __attribute__((aligned(16))) unsigned char rgp_blk2[sizeof(union { char m0[0x0 + sizeof(Query)]; char m1[0xe0d]; })];
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
    for (i = 0; i < 2; i++) {
        r = &self->scene->recs[i];
        if (r == 0) {
            continue;
        }
        if (r->id == 0) {
            continue;
        }
        if (id >= 0 && *r->id != id) {
            continue;
        }
        e = getEnt(self->scene->tbl, r->h10, 2);
        if (e == 0) {
            continue;
        }
        b = (u8 *)e;
        if (b != 0) {
            b += 0x88;
        }
        IterInit_370170(&it[1], b, 0, 0);
        while ((o = ((Node *)IterNext_370040(&it[1]))) != 0) {
            o->w40 = 2;
            if (o->h28 > 0 && o->w30 != 0) {
                p = (*(Query *)(rgp_blk1 + 0x0)).arr;
                do {
                    VariantInit_36ff00(p);
                    p++;
                } while (p < (*(Query *)(rgp_blk1 + 0x0)).arr + 64);
                VariantPoolReset_3e01f0(&(*(Query *)(rgp_blk1 + 0x0)));
                res = ((s32)ScriptExecOpStream_3dffa0(&(*(Query *)(rgp_blk1 + 0x0)), o->h28, o->w30, 0));
                if (res != 0 && VariantIsZero_36ed10(res) != 0) {
                    o->w40 &= ~2;
                    continue;
                }
            }
            if (o->h2A > 0 && o->w34 != 0) {
                p = (*(Query *)(rgp_blk2 + 0x0)).arr;
                do {
                    VariantInit_36ff00(p);
                    p++;
                } while (p < (*(Query *)(rgp_blk2 + 0x0)).arr + 64);
                VariantPoolReset_3e01f0(&(*(Query *)(rgp_blk2 + 0x0)));
                res = ((s32)ScriptExecOpStream_3dffa0(&(*(Query *)(rgp_blk2 + 0x0)), o->h2A, o->w34, 0));
                if (res != 0 && VariantIsZero_36ed10(res) != 0) {
                    o->w40 &= ~2;
                }
            }
        }
    }
    return 1;
}
