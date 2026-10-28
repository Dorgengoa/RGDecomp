/* rgp:protos */
#line 1
#include "types.h"

extern "C" {

class Node {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v60() { return VCM0(s32, 0x60); }
};

struct Sub80 { u8 pad0[8]; u8 *p8; };
typedef struct {
    u8 pad0[2];
    s16 h2;
    s32 w4;
} Part;

typedef struct {
    s16 h0;
    s16 h2;
    Part *p4;
    Part *p8;
    u8 padC[2];
    s16 hE;
    s32 w10;
} Row;

typedef struct {
    u8 pad0[0x7C];
    s16 n7C;
    u8 pad7E[0xE];
    Row *rows;
} Tab;

typedef struct {
    s16 *p0;
    u8 pad4[0xC];
    s16 h10;
} Cur;

typedef struct {
    s16 h0;
    u8 pad2[2];
    s32 w4;
    u8 pad8[0x20];
    Cur *p28;
} Rec;

typedef struct {
    u8 pad0[0x10];
    s32 w10;
    s32 w14;
} Sys;

typedef struct {
    u8 pad0[0x6C];
    s32 w6C;
    u8 pad70[0x10];
    struct Sub80 *p80;
} Sys2;

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    Node *pC;
    Rec *p10;
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
    u8 tail[0x10];
} Big;

s32 VariantIsZero_36ed10(s32);
void VariantInit_36ff00(Elem *);
Node *CharaMgrPoolFindById_3a8c60(s32, s32);
s32 StateVarSet_3cc9c0(s32, s32, s32, s32);
s32 ScriptExecOpStream_3dffa0(Big *, s32, s32, void *);
s32 VariantPoolReset_3e01f0(Big *);
void *ActionPacketInitCharaInteractMaybe_3e2d80(void *, s32, Node *, s32, s32);
s32 EventFireTriggers_3e2660(void *, u8 *);
void InteractRecResetMaybe_3ee600(Out *);
s32 DataTableFindSortedIndex_41eaa0(Tab *, s32);
Rec * GroupGetRecordById_41c2a0(s32, long long, long long, s32);
s32 GetNpcObjTable_312860(void);
Rec *NpcObjFindDefById_2fb490(s32, s32);
extern Sys *D_00483990;
extern Sys2 *D_00483994;

#define TRY(X) { Part *x_ = (X); if (x_ != 0 && x_->h2 > 0 && x_->w4 != 0) { s32 r_ = ScriptExecOpStream_3dffa0(&big, x_->h2, x_->w4, e); if (r_ == 0) continue; if (VariantIsZero_36ed10(r_) != 0) continue; } }
static inline Tab *gettab(struct Sub80 *p, s32 idx) {
    if (idx >= 0) {
        if (idx >= 2) {
            return 0;
        }
        return (Tab *)(p->p8 + idx * 0x98);
    }
    return 0;
}
static inline Row *getrow(Tab *t, s32 i) {
    return (i >= 0 && i < t->n7C) ? &t->rows[i] : 0;
}
static inline Rec *getrec(s32 idB) {
    return GroupGetRecordById_41c2a0(D_00483994->w6C, (long long)(idB), (long long)(-1), 0);
}
Row *InteractRunObjectRowMaybe_3e1d20(void *ctx, s32 arg1, s32 idA, s32 idB, u8 alt, u64 arg5, u64 arg6, Out *out) {
    Rec *rec;
    u8 flag;
    Big big __attribute__((aligned(16)));
    s32 first;
    s32 last;
    s32 key;
    void *e;
    Cur *c;
    Tab *tab;
    Node *a;
    Row *row;
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
        out->h4 = 2;
    }
    a = CharaMgrPoolFindById_3a8c60(D_00483990->w14, idA);
    if (a == 0) {
        return 0;
    }
    if (!alt) {
        rec = NpcObjFindDefById_2fb490(GetNpcObjTable_312860(), idB);
    } else {
        rec = getrec(idB);
    }
    if (rec == 0) {
        return 0;
    }
    key = rec->h0;
    e = ActionPacketInitCharaInteractMaybe_3e2d80(ctx, arg1, a, key, 1);
    if (e == 0) {
        return 0;
    }
    flag = 0;
    EventFireTriggers_3e2660(ctx, &flag);
    if (flag != 0) {
        return 0;
    }
    c = rec->p28;
    if (c == 0) {
        return 0;
    }
    if (c->p0 == 0) {
        return 0;
    }
    tab = gettab(D_00483994->p80, c->h10);
    if (tab == 0) {
        return 0;
    }
    first = DataTableFindSortedIndex_41eaa0(tab, key);
    if (first < 0) {
        return 0;
    }
    last = tab->n7C - 1;
    if (last < first) {
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
    for (i = first; i <= last; i++, row++) {
        if (row->h2 != key) {
            break;
        }
        TRY(row->p4);
        TRY(row->p8);
        StateVarSet_3cc9c0(D_00483990->w10, 0x79, 0, 1);
        if (row->hE > 0 && row->w10 != 0) {
            ScriptExecOpStream_3dffa0(&big, row->hE, row->w10, e);
        }
        if (out != 0) {
        out->h8 = row->h0;
        out->h6 = *c->p0;
        out->w20 = 0;
        out->h0 = idA;
        out->h2 = idB;
        out->w18 = a->v60();
        out->w1C = rec->w4;
        out->pC = a;
        out->p10 = rec;
        out->p14 = row;
        if (alt) {
            out->h2 = -1;
        }
        }
        return row;
    }
    return 0;
}

}
