/* rgp:protos */
#line 1
#include "types.h"
#pragma divbyzerocheck on
#pragma opt_foldconstants off
#pragma opt_arithtransformation off

typedef struct Bits192 {
    u32 w[6];
} Bits192;

typedef struct BitRef {
    Bits192 *b;
    u32 pos;
} BitRef;

typedef struct Key {
    __extension__ unsigned short id : 6;
    unsigned short idx : 3;
    unsigned short kind : 4;
    unsigned short rest : 3;
} __attribute__((aligned(2))) Key;

typedef struct Tile {
    __extension__ unsigned int id : 6;
    unsigned int pad6 : 3;
    unsigned int kind : 4;
    unsigned int conn : 8;
    unsigned int rest : 11;
} __attribute__((aligned(4))) Tile;

typedef struct Cell {
    __extension__ unsigned int f0 : 1;
    unsigned int f1 : 1;
    unsigned int m1 : 8;
    unsigned int m2 : 8;
    unsigned int rest : 14;
} __attribute__((aligned(4))) Cell;

typedef struct Map {
    u32 x0;
    Tile t[1];
} Map;

typedef struct Obj14 {
    u8 pad0[0x14];
    s16 x14;
} Obj14;

typedef struct Tbl {
    u8 pad0[0x4];
    s16 n;
    u8 pad6[2];
    u8 *arr;
} Tbl;

typedef struct Ent {
    s16 *f;
    s16 x4;
    u8 pad6[2];
    Obj14 **list;
    s16 n;
    u8 padE[2];
    s16 *bits;
} Ent;

typedef struct Unit {
    u8 pad0[0x2F0];
    Bits192 bits;
} Unit;

typedef struct Holder {
    u8 pad0[0x10];
    s16 *x10;
} Holder;

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * get(s16 id) { return VCM(void *, (void *, s16), 0x70, id); }
};

typedef struct Sys8C {
    u8 pad0[0xC];
    VObj *xC;
    VObj *x10;
} Sys8C;

typedef struct Sys {
    u8 pad0[0x8C];
    Sys8C *x8C;
} Sys;

typedef struct Ctx {
    u8 pad0[0x8];
    Sys *x8;
    u8 padC[0x14 - 0xC];
    s32 x14;
    s32 x18;
} Ctx;

typedef struct Dbg {
    u8 pad0[0xC];
    s32 xC;
} Dbg;

extern "C" {
extern Dbg *D_00449858[];
extern char D_00466BD0[];
extern char D_00466C00[];

void RevelationBoardCellsClear_3e9aa0(Ctx *, Cell *);
Unit *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
Ent * RevelationBoardCellGetEntry_3eae10(Ctx *, s32, Key *, int);
s16 * RevelationBoardCellGetItemRec_3ead00(Ctx *, s32, Key *, int);
Holder *InvFindByUniqueId_3c85d0(s32, s32, s32, s32);
s32 CharaHasAbilityOrHigher_3adf10(Unit *, s32, s32, s32);
void Fprintf_12f9a0(s32, char *);
void Abort_12de80(void);
s32 Bit64Test_3eee20(Bits192 *, u32);
void BitsetAssignBit_3eedd0(Bits192 *, u32, s32);
void ItemConsume_3d41b0(Holder *, s32, s32, int);
void CharaLearnAbility_3ad460(Unit *, s32, int, int);
Tile *RevelationBoardGetCell_409910(Map *, s32, s32);
}

static inline u16 KeyIdx(Key *k)
{
    return k->idx;
}

static inline u8 KeyKind(Key *k)
{
    return k->kind;
}

static inline s32 Test(Bits192 *b, u32 pos)
{
    BitRef r __attribute__((aligned(16)));
    r.b = b;
    r.pos = pos;
    if (pos >= 192) {
        Fprintf_12f9a0(D_00449858[0]->xC, D_00466BD0);
        Abort_12de80();
    }
    return ((unsigned char)Bit64Test_3eee20(*(Bits192 *volatile *)&r.b, pos));
}

static inline void Set(Bits192 *b, u32 pos, s32 v)
{
    BitRef r __attribute__((aligned(16)));
    r.b = b;
    r.pos = pos;
    if (pos >= 192) {
        Fprintf_12f9a0(D_00449858[0]->xC, D_00466C00);
        Abort_12de80();
    }
    BitsetAssignBit_3eedd0(*(Bits192 *volatile *)&r.b, pos, v);
}

extern "C" s32 RevelationBoardPlaceItemMaybe_3e9b40(Ctx *a, s32 id, Key *key, s32 arg3, Cell *grid)
{
    Unit *u;
    s16 id16;
    Map *o2;
    Ent *e;
    s16 *f;
    s16 *g;
    Holder *h;
    s32 idx;
    s16 *ptr;
    s32 kind;
    s32 bit;
    s32 q, w;
    bool same;
    bool found;
    bool all;
    s16 *pp;
    s32 i;
    Obj14 **pr;
    s32 j;
    Tbl *o1;

    RevelationBoardCellsClear_3e9aa0(a, grid);
    if (key == 0) return -1;
    if (a->x8 == 0) return -1;
    u = CharaMgrPoolFindByDataId_3a8a70(a->x14, id, 1, 1, 0, 0, 0);
    if (u == 0) return -1;
    id16 = id;
    o1 = (Tbl *)a->x8->x8C->xC->get(id16);
    if (o1 == 0) return -1;
    o1 = o1;
    o2 = (Map *)a->x8->x8C->x10->get(id16);
    if (o2 == 0) return -1;
    e = RevelationBoardCellGetEntry_3eae10(a, id, key, 0);
    if (e == 0) return -1;
    f = e->f;
    if (f == 0) return -1;
    g = RevelationBoardCellGetItemRec_3ead00(a, id, key, 0);
    if (g == 0) return -1;
    h = InvFindByUniqueId_3c85d0(a->x18, arg3, 0, 0);
    if (h == 0) return -1;
    ptr = 0;
    if ((idx = (u16)key->idx) >= 0 && idx < e->n) ptr = (s16 *)((u8 *)e->bits + idx * 4);
    if (ptr == 0) return -1;
    kind = (u8)key->kind;
    if (kind == 14) goto z;
    if (kind == 13) { z: return 0; }
    if (((unsigned char)CharaHasAbilityOrHigher_3adf10(u, *f, 0, 0)) != 0) return 0;
    bit = *ptr;
    if (Test(&u->bits, bit)) return 0;
    q = *g;
    w = *h->x10;
    same = 0;
    if (q == w) same = 1;
    if (!same) {
        if (q == 0x40F2 && w == 0x410B) return -2;
        return -1;
    }
    Set(&u->bits, *ptr, 1);
    ItemConsume_3d41b0(h, 1, 1, 0);
    pp = e->bits;
    found = 0;
    all = 1;
    for (i = 0; i < e->n; i++, pp = (s16 *)((u8 *)pp + 4)) {
        if (!Test(&u->bits, *pp)) {
            all = 0;
            break;
        }
    }
    if (all) {
        found = 1;
        CharaLearnAbility_3ad460(u, *f, 0, 0);
        if (grid != 0) {
            Tile *t = o2->t;
            Cell *c = grid;
            s32 n;
            for (n = 0; n < 0x1D4; n++, t++, c++) {
                if ((*(u8 *)t & 0x3F) == (*(u8 *)key & 0x3F)) {
                    s32 r = n / 26;
                    s32 cc = n % 26;
                    Tile *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7;
                    Cell *p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7;
                    c->f0 = 1;
                    n0 = RevelationBoardGetCell_409910(o2, r - 1, cc - 1);
                    n1 = RevelationBoardGetCell_409910(o2, r - 1, cc);
                    n2 = RevelationBoardGetCell_409910(o2, r - 1, cc + 1);
                    n3 = RevelationBoardGetCell_409910(o2, r, cc - 1);
                    n4 = RevelationBoardGetCell_409910(o2, r, cc + 1);
                    n5 = RevelationBoardGetCell_409910(o2, r + 1, cc - 1);
                    n6 = RevelationBoardGetCell_409910(o2, r + 1, cc);
                    n7 = RevelationBoardGetCell_409910(o2, r + 1, cc + 1);
                    p0 = 0;
                    p1 = 0;
                    p2 = 0;
                    p3 = 0;
                    p4 = 0;
                    p5 = 0;
                    p6 = 0;
                    p7 = 0;
                    if (r - 1 >= 0) {
                        if (cc - 1 >= 0) p0 = &grid[(r - 1) * 26 + (cc - 1)];
                        p1 = &grid[(r - 1) * 26 + cc];
                        if (cc + 1 < 26) p2 = &grid[(r - 1) * 26 + (cc + 1)];
                    }
                    if (cc - 1 >= 0) p3 = &grid[r * 26 + (cc - 1)];
                    if (cc + 1 < 26) p4 = &grid[r * 26 + (cc + 1)];
                    if (r + 1 < 18) {
                        if (cc - 1 >= 0) p5 = &grid[(r + 1) * 26 + (cc - 1)];
                        p6 = &grid[(r + 1) * 26 + cc];
                        if (cc + 1 < 26) p7 = &grid[(r + 1) * 26 + (cc + 1)];
                    }
                    if (p0) p0->m1 = p0->m1 | (u16)(n0->conn & 0x80);
                    if (p1) p1->m1 = p1->m1 | (u16)(n1->conn & 0xE0);
                    if (p2) p2->m1 = p2->m1 | (u16)(n2->conn & 0x20);
                    if (p3) p3->m1 = p3->m1 | (u16)(n3->conn & 0x94);
                    if (p4) p4->m1 = p4->m1 | (u16)(n4->conn & 0x29);
                    if (p5) p5->m1 = p5->m1 | (u16)(n5->conn & 0x04);
                    if (p6) p6->m1 = p6->m1 | (u16)(n6->conn & 0x07);
                    if (p7) p7->m1 = p7->m1 | (u16)(n7->conn & 0x01);
                }
            }
            {
                pr = e->list;
                for (j = 0; j < e->x4; j++, pr++) {
                    Obj14 *ob = *pr;
                    if (ob != 0 && ob->x14 == 10) {
                        Tile *t2 = o2->t;
                        Cell *c2 = grid;
                        s32 n2;
                        for (n2 = 0; n2 < 0x1D4; n2++, t2++, c2++) {
                            s32 k = t2->id;
                            if (k >= 0 && k < o1->n && t2->kind == 10 && (u8 *)ob == o1->arr + k * 0x1C) {
                                s32 r = n2 / 26;
                                s32 cc = n2 % 26;
                                Tile *n0, *n1, *nn2, *n3, *n4, *n5, *n6, *n7;
                                Cell *p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7;
                                c2->f1 = 1;
                                n0 = RevelationBoardGetCell_409910(o2, r - 1, cc - 1);
                                n1 = RevelationBoardGetCell_409910(o2, r - 1, cc);
                                nn2 = RevelationBoardGetCell_409910(o2, r - 1, cc + 1);
                                n3 = RevelationBoardGetCell_409910(o2, r, cc - 1);
                                n4 = RevelationBoardGetCell_409910(o2, r, cc + 1);
                                n5 = RevelationBoardGetCell_409910(o2, r + 1, cc - 1);
                                n6 = RevelationBoardGetCell_409910(o2, r + 1, cc);
                                n7 = RevelationBoardGetCell_409910(o2, r + 1, cc + 1);
                                p0 = 0;
                                p1 = 0;
                                p2 = 0;
                                p3 = 0;
                                p4 = 0;
                                p5 = 0;
                                p6 = 0;
                                p7 = 0;
                                if (r - 1 >= 0) {
                                    if (cc - 1 >= 0) p0 = &grid[(r - 1) * 26 + (cc - 1)];
                                    p1 = &grid[(r - 1) * 26 + cc];
                                    if (cc + 1 < 26) p2 = &grid[(r - 1) * 26 + (cc + 1)];
                                }
                                if (cc - 1 >= 0) p3 = &grid[r * 26 + (cc - 1)];
                                if (cc + 1 < 26) p4 = &grid[r * 26 + (cc + 1)];
                                if (r + 1 < 18) {
                                    if (cc - 1 >= 0) p5 = &grid[(r + 1) * 26 + (cc - 1)];
                                    p6 = &grid[(r + 1) * 26 + cc];
                                    if (cc + 1 < 26) p7 = &grid[(r + 1) * 26 + (cc + 1)];
                                }
                                if (p0) p0->m2 = p0->m2 | (n0->conn & 0x80);
                                if (p1) p1->m2 = p1->m2 | (n1->conn & 0xE0);
                                if (p2) p2->m2 = p2->m2 | (nn2->conn & 0x20);
                                if (p3) p3->m2 = p3->m2 | (n3->conn & 0x94);
                                if (p4) p4->m2 = p4->m2 | (n4->conn & 0x29);
                                if (p5) p5->m2 = p5->m2 | (n5->conn & 0x04);
                                if (p6) p6->m2 = p6->m2 | (n6->conn & 0x07);
                                if (p7) p7->m2 = p7->m2 | (n7->conn & 0x01);
                            }
                        }
                        {
                            s32 n3;
                            Tile *t3 = o2->t;
                            Cell *c3 = grid;
                            for (n3 = 0; n3 < 0x1D4; n3++, t3++, c3++) {
                                if (t3->kind == 1 && (c3->m2 & 2)) c3->f1 = 1;
                                if (t3->kind == 3 && (c3->m2 & 8)) c3->f1 = 1;
                                if (t3->kind == 4 && (c3->m2 & 0x10)) c3->f1 = 1;
                                if (t3->kind == 2 && (c3->m2 & 0x40)) c3->f1 = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (!found) {
        if (w == 0x40F2) return 3;
        return 1;
    }
    if (w == 0x40F2) return 4;
    return 2;
}
