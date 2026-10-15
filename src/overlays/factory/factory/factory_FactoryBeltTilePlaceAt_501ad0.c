#include "types.h"

/* factory.bin overlay, 0x00501AD0 -- place a single-cell item on the coarse
 * grid: take the next free slot, stamp the cell, seat the node's transform and
 * open the trailing marker slot.  660 bytes.
 */

typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;

typedef struct Node {
    u8  pad00[0x32];
    s16 f32;
} Node;

typedef struct Slot {
    u8    pad00[0x20];
    Node *f20;
    s8    f24;
    s8    f25;
    s8    f26;
    s8    f27;
    s16   f28;
    s16   f2A;
    u8    pad2C[0x4];
    s16   f30;
    s16   f32;
} Slot;

typedef struct List {
    u8  pad00[0xA];
    s16 f0A;
    s16 f0C;
} List;

typedef struct Ctx {
    u8    pad000[0x294];
    Cell *f294;
    s16   f298;
} Ctx;

extern List *factory_FactoryBeltTileGroupFindById_5040d0(void);
extern Slot *factory_FactoryBeltTileGroupGetObj_4ff180(List *l, s16 id);
extern s32 factory_FactoryFineGridCellIsFree_502d20(Ctx *c, List *l, s32 x, s32 y);
extern f32 factory_FactoryFineGridCellCenterX_5037c0(Ctx *c, s32 x);
extern f32 factory_FactoryFineGridCellCenterZ_503790(Ctx *c, s32 y);
extern f32 factory_FactoryGridDirToAngle_4ff990(s32 kind);
extern void func_1866B0(Node *nd, f32 *v);
extern void func_186620(Node *nd, f32 *v);
extern void func_1865B0(Node *nd, f32 *v);

s32 factory_FactoryBeltTilePlaceAt_501ad0(Ctx *c, s16 tag, s32 x, s32 y, s32 kind)
{
    f32   v1[4];
    f32   v2[4];
    f32   v3[4];
    List *l;
    Slot *h;
    Slot *g;
    Node *nd;
    Cell *p;
    f32   gx;
    f32   gy;
    f32   rot;
    s16   n;
    s16   k;
    s8   *q;
    u32   m;

    l = factory_FactoryBeltTileGroupFindById_5040d0();
    if (l == NULL) {
        return 0;
    }
    n = l->f0C;
    if (l->f0A <= n) {
        return 0;
    }
    h = factory_FactoryBeltTileGroupGetObj_4ff180(l, n);
    if (h == NULL) {
        return 0;
    }
    if (factory_FactoryFineGridCellIsFree_502d20(c, l, x, y) == 0) {
        return 0;
    }
    p = c->f294 + y * c->f298 + x;
    p->f00 = tag;
    p->f02 = l->f0C;
    p->f04 = (((p->f04 & ~3) | kind) & 3);
    gx = factory_FactoryFineGridCellCenterX_5037c0(c, x);
    gy = factory_FactoryFineGridCellCenterZ_503790(c, y);

    nd = h->f20;
    q = (s8 *)v1;
    m = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            m--;
            q++;
        } while (m != 0);
    }
    v1[0] = gx;
    v1[1] = 0.0f;
    v1[2] = gy;
    func_1866B0(nd, v1);

    rot = factory_FactoryGridDirToAngle_4ff990(kind);
    nd = h->f20;
    q = (s8 *)v2;
    m = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            m--;
            q++;
        } while (m != 0);
    }
    v2[0] = 0.0f;
    v2[1] = rot;
    v2[2] = 0.0f;
    func_186620(nd, v2);

    nd = h->f20;
    q = (s8 *)v3;
    m = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            m--;
            q++;
        } while (m != 0);
    }
    v3[0] = 1.0f;
    v3[1] = 1.0f;
    v3[2] = 1.0f;
    func_1865B0(nd, v3);

    h->f20->f32 = 1;
    h->f24 = 0;
    h->f25 = 3;
    h->f26 = (s8)((h->f26 & ~3) | (kind & 3));
    h->f27 = 0;
    h->f28 = 0;
    h->f30 = x;
    h->f32 = y;
    k = l->f0C + 1;
    l->f0C = k;
    g = factory_FactoryBeltTileGroupGetObj_4ff180(l, k);
    if (g != NULL) {
        g->f24 = -1;
        g->f25 = 0;
        g->f26 = 0;
        g->f27 = 0;
        g->f28 = 0;
        g->f2A = 0;
        g->f30 = -1;
        g->f32 = -1;
    }
    return 1;
}
