/* rgp:protos */
#line 1
#pragma opt_dead_assignments off
#include "types.h"

#pragma opt_scalarize off

#pragma opt_foldconstants off
#pragma opt_arithtransformation off

typedef struct Iter { s32 a; s32 b; } Iter;
typedef struct Key { u8 *p; s32 id; } Key;

typedef struct Ref {
    s16 m0;
    s16 m2;
} Ref;

typedef struct Ev Ev;
struct Ev {
    s16 *m0;
    s16 m4;
    s16 pad6;
    Ev **m8;
    s16 mC;
    s16 padE;
    Ref *m10;
    s16 m14;
    s16 m16;
    u8 m18;
    u8 pad19[3];
};

typedef struct Scr {
    s16 m0;
    u8 pad2[2];
    s16 m4;
    u8 pad6[2];
    Ev *m8;
    s16 mC;
    u8 padE[2];
    s16 **m10;
} Scr;

typedef struct Cell {
    __extension__ unsigned short id : 6;
    unsigned short idx : 3;
    unsigned short st : 4;
    unsigned short pad : 3;
    u16 hi;
} __attribute__((aligned(2))) Cell;

class Tbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * f70(s32 a0) { return VCM(u8 *, (void *, s32), 0x70, a0); }
};

typedef struct Sub8C { u8 pad0[0xC]; u8 *mC; Tbl *m10; } Sub8C;
typedef struct Sub8 { u8 pad0[0x8C]; Sub8C *m8C; } Sub8;

typedef struct Arg0 {
    u8 pad0[8];
    Sub8 *m8;
    u8 padC[4];
    s32 m10;
    s32 m14;
    s32 m18;
} Arg0;

typedef struct G { u8 pad0[0xC]; s32 mC; } G;

extern "C" {
void Abort_12de80(void);
void Fprintf_12f9a0(s32, u8 *);
Scr *IterNext_370040(Iter *);
void IterReset_3700f0(Iter *);
void IterInit_370170(Iter *, u8 *, int, int);
u8 *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
s32 CharaHasAbilityOrHigher_3adf10(u8 *, s32, s32, s32);
s32 InvHasItemInCategory_3c7f40(s32, s32, s32, s32);
void StateVarSet_3cc9c0(s32, s32, s16, s32);
void StateFlagSet_3ccb70(s32, s32, bool, s32);
void RevelationBoardCellsClear_3e9aa0(Arg0 *, s32);
void BitsetAssignBit_3eedd0(u8 *, s32, s32);
s32 Bit64Test_3eee20(u8 *, s32);
void RevelationBoardCellSetLevel_409410(u8 *, s32, s32, s32);
void RevelationBoardEntryRaiseState_409960(Ev *, s32);
Ev *RevelationBoardGetEntry_409990(Scr *, s32);
extern G *D_00449858[0x100];
extern u8 D_00466BD0[0x400];
extern u8 D_00466C00[0x400];
extern f32 D_0047D1DC;
s32 RevelationBoardRefreshMaybe_3eaec0(Arg0 *arg0, s32 filt, s32 arg2);
}

static inline u8 Has(u8 *obj, s32 id)
{
    Key k __attribute__((aligned(16)));

    k.p = obj + 0x2F0;
    k.id = id;
    if ((u32)id >= 0xC0) {
        Fprintf_12f9a0(D_00449858[0]->mC, D_00466BD0);
        Abort_12de80();
    }
    return (u8)((unsigned char)Bit64Test_3eee20(k.p, id));
}

static inline s32 Has2(u8 *obj, s32 id)
{
    Key k __attribute__((aligned(16)));

    k.p = obj + 0x2F0;
    k.id = id;
    if ((u32)id >= 0xC0) {
        Fprintf_12f9a0(D_00449858[0]->mC, D_00466BD0);
        Abort_12de80();
    }
    return ((unsigned char)Bit64Test_3eee20(k.p, id));
}

static inline void Set(u8 *obj, s32 id)
{
    Key k __attribute__((aligned(16)));

    k.p = obj + 0x2F0;
    k.id = id;
    if ((u32)id >= 0xC0) {
        Fprintf_12f9a0(D_00449858[0]->mC, D_00466C00);
        Abort_12de80();
    }
    BitsetAssignBit_3eedd0(k.p, id, 0);
}

s32 RevelationBoardRefreshMaybe_3eaec0(Arg0 *arg0, s32 filt, s32 arg2)
{
    Iter it __attribute__((aligned(16)));
    Scr *s;
    u8 *base;
    u8 *obj;
    s32 id;
    Ev *e;
    s32 i;
    Ev **pp;
    s32 j;
    s32 k;
    bool any;
    Ref *r;
    u8 *t;
    Cell *c;
    s32 row;
    s32 col;
    s32 rb;
    Ev *q;
    s32 idx;
    Ref *rr;
    s16 *sp7;
    s32 ref;
    s32 ty;
    s32 ok;
    s32 total;
    s32 hit;
    s32 pct;
    bool full;
    s32 j_w72;
    s32 j_w83;

    if (arg0->m8 == 0) {
        return 0;
    }
    RevelationBoardCellsClear_3e9aa0(arg0, arg2);
    if ((base = arg0->m8->m8C->mC) != 0) {
        base += 0x88;
    }
    IterInit_370170(&it, base, 0, 0);
    while (s = IterNext_370040(&it), s != 0) {
        s = s;
        if (filt >= 0 && s->m0 != filt) {
            continue;
        }
        id = s->m0;
        if ((obj = CharaMgrPoolFindByDataId_3a8a70(arg0->m14, id, 1, 1, 0, 0, 0)) == 0) {
            continue;
        }
        e = s->m8;
        for (i = 0; i < s->m4; i++, e++) {
            if (e->m0 == 0) {
                continue;
            }
            if ((u8)((unsigned char)CharaHasAbilityOrHigher_3adf10(obj, *e->m0, 1, 0))) {
                RevelationBoardEntryRaiseState_409960(e, 0xE);
                pp = e->m8;
                for (j = 0; j < e->m4; j++, pp++) {
                    if (*pp == 0) {
                        continue;
                    }
                    if ((*pp)->m14 < 0xB) {
                        RevelationBoardEntryRaiseState_409960(*pp, 0xB);
                    }
                }
            } else if (e->m18 & 1) {
                RevelationBoardEntryRaiseState_409960(e, 0xB);
            }
        }
        e = s->m8;
        for (k = 0; k < s->m4; k++, e++) {
            if (e->m14 != 0xB) {
                continue;
            }
            any = false;
            r = e->m10;
            for (j_w72 = 0; j_w72 < e->mC; j_w72++, r++) {
                if (Has(obj, r->m0)) {
                    any = true;
                }
            }
            if (any > 0) {
                if (any < e->mC) {
                    RevelationBoardEntryRaiseState_409960(e, 0xD);
                } else {
                    r = e->m10;
                    for (j_w83 = 0; j_w83 < e->mC; j_w83++, r++) {
                        Set(obj, r->m0);
                    }
                }
            }
        }
        if ((t = arg0->m8->m8C->m10->f70((s16)id)) == 0) {
            continue;
        }
        c = (Cell *)(t + 4);
        for (row = 0; row < 0x12; row++) {
            rb = row * 26;
            for (col = 0; col < 0x1A; col++, c++) {
                if (c->st < 10) {
                    continue;
                }
                c->st = 10;
                if ((q = RevelationBoardGetEntry_409990(s, c->id)) == 0) {
                    continue;
                }
                if (q->m16 < 0) {
                    q->m16 = col + rb;
                }
                sp7 = 0;
                ref = -1;
                if ((idx = (u16)c->idx) >= 0 && idx < q->mC) {
                    rr = &q->m10[idx];
                    ref = rr->m0;
                    if ((idx = rr->m2) >= 0 && idx < s->mC) {
                        sp7 = s->m10[idx];
                    }
                }
                ty = q->m14;
                if (sp7 == 0 || ref >= 0) {
                    if (ty == 0xD) {
                        if (Has2(obj, ref)) {
                            ty = 0xD;
                        } else {
                            ty = 0xB;
                        }
                    }
                    if (ty == 0xB && sp7 != 0) {
                        ref = *sp7;
                        if ((ok = InvHasItemInCategory_3c7f40(arg0->m18, ref, 0, 0) & 0xFF) == 0 && ref == 0x40F2) {
                            ok = InvHasItemInCategory_3c7f40(arg0->m18, 0x410B, 0, 0) & 0xFF;
                        }
                        if (ok != 0) {
                            ty = 0xC;
                        }
                    }
                } else {
                    ty = 10;
                }
                RevelationBoardCellSetLevel_409410(t, row, col, ty);
            }
        }
    }
    total = 0;
    hit = 0;
    IterReset_3700f0(&it);
    while ((s = IterNext_370040(&it)) != 0) {
        if ((obj = CharaMgrPoolFindByDataId_3a8a70(arg0->m14, s->m0, 1, 1, 0, 0, 0)) == 0) {
            continue;
        }
        e = s->m8;
        for (i = 0; i < s->m4; i++, e++) {
            if (e->m0 == 0) {
                continue;
            }
            total++;
            if ((u8)((unsigned char)CharaHasAbilityOrHigher_3adf10(obj, *e->m0, 1, 0))) {
                hit++;
            }
        }
    }
    pct = (s32)(D_0047D1DC + 100.0f * ((f32)hit / (f32)total));
    full = false;
    if (pct < 0) {
        pct = 0;
    } else if (pct >= 100) {
        full = true;
        pct = 100;
    }
    StateFlagSet_3ccb70(arg0->m10, 0x1E5, full, 0);
    StateVarSet_3cc9c0(arg0->m10, 0x69, pct, 0);
    return 1;
}
