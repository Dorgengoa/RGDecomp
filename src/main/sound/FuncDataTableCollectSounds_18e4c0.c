#include "types.h"
#pragma opt_loop_invariants off

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Item {
    u8 pad[0x44];
    s32 f44;
    s32 f48;
    u8 pad4C[0xC];
    f32 f58;
    f32 f5C;
    s32 f60;
    f32 f64;
    f32 f68;
    u8 pad6C[4];
    s32 f70;
    u8 pad74[8];
    s32 f7C;
    Vec f80;
    Vec f90;
} Item;

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    Item *item;
} Node;

typedef struct Head {
    u8 pad[8];
    Node *firstA;
    u8 padC[0x14];
    Node *firstB;
} Head;

typedef struct List {
    u8 pad[4];
    Head *head;
    Node *cur;
} List;

void MtxMulPoint_13c890(Vec *, void *, Vec *);
void MtxMulVec4_13c900(Vec *, void *, Vec *);
void MtxMul_13d240(Vec *, Vec *, void *);
void NodeCalcWorldMatrix_186130(Item *, Vec *);
void NodeGetTranslation_186650(Item *, Vec *);
void SoundCalcSegmentVolPan_1b7d30(f32 *, s32 *, Vec *, Vec *, f32, f32);
void SoundCalcDistVolPan_1b7de0(f32 *, s32 *, Vec *, f32, f32);

static inline void BeginA(List *l) {
    l->cur = 0;
    if (l->head != 0) {
        l->cur = l->head->firstA;
    }
}

static inline void BeginB(List *l) {
    l->cur = 0;
    if (l->head != 0) {
        l->cur = l->head->firstB;
    }
}

static inline Item *Next(List *l) {
    Node *n = l->cur;
    if (n == 0) {
        return 0;
    }
    l->cur = n->next;
    return n->item;
}

static inline void End(List *l) {
    l->cur = 0;
}

static inline s32 Visible(Item *it, f32 *pos) {
    f32 lo;
    f32 hi;
    f32 x;
    if (it->f44 == 0) {
        return 0;
    }
    if (pos == 0) {
        return 1;
    }
    hi = it->f5C;
    lo = it->f58;
    x = *pos;
    if (!(hi <= lo)) {
        if (x < lo) return 0;
        if (!(x < hi)) return 0;
        return 1;
    }
    {
        s32 r;
        if (lo <= hi) goto one;
        if (!(x < lo)) {
            r = 1;
            goto end;
        }
        if (x < hi) {
            r = 1;
            goto end;
        }
        r = 0;
        goto end;
    one:
        r = 1;
    end:
        return r;
    }
}

s32 FuncDataTableCollectSounds_18e4c0(void *mtx, List *l, f32 *pos, s32 *ids, f32 *outf, s32 *outx, s32 max) {
    Vec v;
    Vec v2;
    Vec m[4];
    Item *it;
    s32 n;
    s32 cnt;

    n = 0;
    BeginA(l);
    while ((it = Next(l)) != 0) {
        it->f48 = Visible(it, pos);
    }
    End(l);
    BeginA(l);
    while ((it = Next(l)) != 0) {
        if (it->f48 == 0) {
            continue;
        }
        if (n >= max) {
            return n;
        }
        if (it->f7C <= 0) {
            continue;
        }
        NodeGetTranslation_186650(it, &v);
        v.w = 1.0f;
        MtxMulVec4_13c900(&v, mtx, &v);
        SoundCalcDistVolPan_1b7de0(outf, outx, &v, 10.0f, 400.0f);
        if (!(*outf <= 0.0f)) {
            outf++;
            outx++;
            n++;
            *ids++ = it->f7C;
        }
    }
    End(l);
    BeginB(l);
    cnt = 0;
    while ((it = Next(l)) != 0) {
        if ((it->f48 = Visible(it, pos)) != 0) {
            cnt++;
        }
    }
    End(l);
    if (cnt > 0) {
        BeginB(l);
        while ((it = Next(l)) != 0) {
            if (it->f48 == 0) {
                continue;
            }
            if (n >= max) {
                return n;
            }
            if (it->f70 == 1) {
                NodeCalcWorldMatrix_186130(it, m);
                MtxMul_13d240(m, m, mtx);
                MtxMulVec4_13c900(&v, m, &it->f80);
                MtxMulVec4_13c900(&v2, m, &it->f90);
                SoundCalcSegmentVolPan_1b7d30(outf, outx, &v, &v2, it->f64, it->f68);
            } else {
                NodeGetTranslation_186650(it, &v);
                MtxMulPoint_13c890(&v, mtx, &v);
                SoundCalcDistVolPan_1b7de0(outf, outx, &v, it->f64, it->f68);
            }
            if (!(*outf <= 0.0f)) {
                outf++;
                outx++;
                n++;
                *ids++ = it->f60;
            }
        }
        End(l);
    }
    return n;
}
