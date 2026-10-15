#include "types.h"

typedef struct Ent {
    s16 f00;
} Ent;

typedef struct Item {
    Ent *f00;
    s16  f04;
    u8   pad06[0x2];
    u8   f08;
    u8   pad09[0x7];
} Item;                                         /* 0x10 */

typedef struct List {
    u8    pad00[0x8];
    s16   f08;
    u8    pad0A[0x2];
    Item *f0C;
} List;

typedef struct Ctx {
    u8    pad00[0x70];
    List *f70;
} Ctx;

typedef struct Obj {
    u8    pad00[0x40];
    void *f40;
    void *f44;
} Obj;

typedef struct Ret {
    u8  pad00[0x14];
    s16 f14;
} Ret;

typedef struct World {
    u8    pad00[0x18];
    void *f18;
} World;

extern Ctx *D_00484A48;                         /* _gp - 0x728 */

extern void   func_291250(void *h, s32 id, s32 a, s64 b);
extern Ret   *func_28EA40(void *h, s32 id);
extern World *func_1FEDE0(void);
extern s32    func_3C78D0(void *h, s32 id, s32 a, s32 b);
extern Ent   *factory_FactoryMaterialGetCellItem_4f3290(Obj *o);

void factory_FactoryMaterialQtyPreset_4f2bf0(Obj *o)
{
    Ret   *r;
    List  *l;
    World *w;
    Ent   *q;
    Item  *p;
    s32    i;
    s32    n;
    u8     go;

    func_291250(o->f40, 0x79, 0, 0);
    r = func_28EA40(o->f44, 0x8930);
    r->f14 = 0;
    l = D_00484A48->f70;
    if (l == 0) {
        return;
    }
    w = func_1FEDE0();
    if (w == 0) {
        return;
    }
    q = factory_FactoryMaterialGetCellItem_4f3290(o);
    if (q == 0) {
        return;
    }
    p = l->f0C;
    go = 1;
    for (i = 0; i < l->f08 && go; i++, p++) {
        if (q->f00 == p->f00->f00) {
            if ((p->f08 & 1) != 0) {
                n = func_3C78D0(w->f18, q->f00, 0, 0);
                if (n >= p->f04) {
                    func_291250(o->f40, 0x79, 0, p->f04);
                    r->f14 = p->f04;
                } else {
                    func_291250(o->f40, 0x79, 0, n);
                    r->f14 = n;
                }
                go = 0;
            }
        }
    }
}
