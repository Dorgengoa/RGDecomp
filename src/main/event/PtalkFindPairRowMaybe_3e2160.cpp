#include "types.h"

extern "C" {

class Node {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual s32 v5C();
    virtual s32 v60();
};

struct Sub7C { u8 pad0[8]; u8 *p8; };
typedef struct {
    u8 pad0[2];
    s16 h2;
    s32 w4;
} Part;

typedef struct {
    s16 h0;
    u8 pad2[2];
    Part *p4;
    Part *p8;
    Part *pC;
    u8 pad10[2];
    s16 h12;
    s32 w14;
} Row;

typedef struct {
    u8 pad0[0x7C];
    s16 n7C;
    u8 pad7E[0xE];
    Row *rows;
} Tab;

typedef struct {
    s16 **pp;
    u8 pad4[4];
    s16 h8;
} Cur;

typedef struct {
    u8 pad0[8];
    struct { u8 pad0[0xC]; u8 *pC; } *p8;
    u8 padC[4];
    s32 w10;
    s32 w14;
    struct { u8 pad0[0x32]; s16 h32; } *p18;
} Sys;

typedef struct {
    u8 pad0[0x7C];
    struct Sub7C *p7C;
} Sys2;

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    Node *pC;
    Node *p10;
    Row *p14;
    s32 w18;
    s32 w1C;
    s32 w20;
} Out;

typedef struct {
    u8 d[0x38];
} Elem;

typedef struct {
    u8 hdr[8];
    Elem e[64];
} Big;

s32 VariantIsZero_36ed10(s32);
s32 VariantInit_36ff00(Elem *);
Node *CharaMgrPoolFindById_3a8c60(s32, s32);
s32 StateVarSet_3cc9c0(s32, s32, s32, s32);
s32 ScriptExecOpStream_3dffa0(Big *, s32, s32, void *);
s32 VariantPoolReset_3e01f0(Big *);
void *ActionPacketInitCharaPairMaybe_3e2e90(void *, s32, Node *, Node *, s32);
s32 EventFireTriggers_3e2660(void *, u8 *);
Cur *PlanetEntryGetCurrentMaybe_3ec530(Sys *);
s32 InteractRecResetMaybe_3ee600(Out *);
s32 PtalkParamGetCharaRowRange_420510(Tab *, s32, s32 *, s32 *);
extern s32 D_00465D30[];
extern Sys *D_00483990;
extern Sys2 *D_00483994;

static inline s32 Try(Big *big, Part *x, void *e) {
    s32 r;
    if (x != 0 && x->h2 > 0 && x->w4 != 0) {
        r = ScriptExecOpStream_3dffa0(big, x->h2, x->w4, e);
        if (r == 0) {
            return 0;
        }
        if (VariantIsZero_36ed10(r) != 0) {
            return 0;
        }
    }
    return 1;
}

#define TRY(X) { Part *x_ = (X); if (x_ != 0 && x_->h2 > 0 && x_->w4 != 0) { s32 r_ = ScriptExecOpStream_3dffa0(&big, x_->h2, x_->w4, e); if (r_ == 0) continue; if (VariantIsZero_36ed10(r_) != 0) continue; } }
static inline Tab *gettab(struct Sub7C *p, s32 idx) {
    if (idx >= 0) {
        if (idx >= 2) {
            return 0;
        }
        return (Tab *)(p->p8 + idx * 0xC0);
    }
    return 0;
}
static inline Row *getrow(Tab *t, s32 i) {
    return (i >= 0 && i < t->n7C) ? &t->rows[i] : 0;
}
Row *PtalkFindPairRowMaybe_3e2160(void *ctx, s32 arg1, s32 idA, s32 idB, Out *out) {
    u8 flag;
    s32 first;
    s32 last;
    Big big;
    s32 k;
    void *e;
    Cur *c;
    u8 *q;
    s32 idx;
    Tab *tab;
    Node *a;
    Row *row;
    Node *b;
    Elem *el;
    s32 i;

    if (idA < 0 || idB < 0) {
        return 0;
    }
    if (D_00483990 == 0 || D_00483994 == 0) {
        return 0;
    }
    if (out != 0) {
        InteractRecResetMaybe_3ee600(out);
        out->h4 = 1;
    }
    a = CharaMgrPoolFindById_3a8c60(D_00483990->w14, idA);
    if (a == 0) {
        return 0;
    }
    b = CharaMgrPoolFindById_3a8c60(D_00483990->w14, idB);
    if (b == 0) {
        return 0;
    }
    k = b->v5C();
    if (k < 0) {
        return 0;
    }
    e = ActionPacketInitCharaPairMaybe_3e2e90(ctx, arg1, a, b, 1);
    if (e == 0) {
        return 0;
    }
    flag = 0;
    EventFireTriggers_3e2660(ctx, &flag);
    if (flag != 0) {
        return 0;
    }
    c = PlanetEntryGetCurrentMaybe_3ec530(D_00483990);
    if (c == 0) {
        return 0;
    }
    if (c->pp == 0) {
        return 0;
    }
    if (**(s16 **)c == 1) {
        if (D_00483990->p18->h32 == D_00465D30[0] || D_00483990->p18->h32 == 0x438) {
            q = D_00483990->p8->pC + 0x1C;
            if (q != 0 && *(s32 *)q != 0) {
                c = (Cur *)q;
            }
        }
    }
    tab = gettab(D_00483994->p7C, c->h8);
    if (tab == 0) {
        return 0;
    }
    first = -1;
    last = -1;
    PtalkParamGetCharaRowRange_420510(tab, k, &first, &last);
    if (first < 0 || last < 0) {
        return 0;
    }
    el = big.e;
    do {
        VariantInit_36ff00(el);
        el++;
    } while ((u32)el < (u32)&big.e[64]);
    VariantPoolReset_3e01f0(&big);
    row = getrow(tab, first);
    if (row == 0) {
        return 0;
    }
    for (i = *(volatile s32 *)&first; i <= last; i++, row++) {
        TRY(row->p4);
        TRY(row->p8);
        TRY(row->pC);
        StateVarSet_3cc9c0(D_00483990->w10, 0x79, 0, 1);
        if (row->h12 > 0 && row->w14 != 0) {
            ScriptExecOpStream_3dffa0(&big, row->h12, row->w14, e);
        }
        if (out != 0) {
        out->h8 = row->h0;
        out->h6 = **(s16 **)c;
        out->w20 = 0;
        out->h0 = idA;
        out->h2 = idB;
        out->w18 = a->v60();
        out->w1C = b->v60();
        out->pC = a;
        out->p10 = b;
        out->p14 = row;
        }
        return row;
    }
    return 0;
}

}
