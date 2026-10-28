/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialGridBuild_4f3560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s16 f00;
    s8  f02;
    s8  f03;
    s16 f04;
    u8  pad06[0x26];
    s16 f2C;
} Ent;

typedef struct Row {
    u8  pad00[0x8];
    s64 f08;
    u8  pad10[0x10];
} Row;                                          /* 0x20 */

typedef struct Ctx {
    u8    pad00[0xE];
    s8    f0E[0x10];
    u8    pad1E[0x22];
    void *f40;
} Ctx;

typedef struct Iter { u8 pad[0x8]; } Iter;
typedef struct Filt { u8 pad[0x20]; } Filt;

typedef struct World {
    u8    pad00[0x8];
    void *f08;
    u8    pad0C[0xC];
    void *f18;
} World;

typedef struct Zone {
    u8    pad00[0x40];
    void *f40;
} Zone;

typedef struct Area {
    u8  pad00[0x8];
    s32 f08;
} Area;

extern s32 factory_D_0050CB40[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void   memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialGridBuild_4f3560(Ctx *a, s32 b, s32 c)
{
    Filt   filt __attribute__((aligned(16)));
    Iter   it3 __attribute__((aligned(16)));
    Iter   it2 __attribute__((aligned(16)));
    World *w;
    Row   *rows;
    Ent   *e;
    s32    i;
    s32    id;
    s32    key;
    s32   *tab;
    s32    n;

    e = (Ent *)c;
    w = ((World *)GetGameData_1fede0());
    if (w == 0) {
        return 0;
    }
    id = (u16)(s8)(b + 1);
    rows = ((Row *)UiGetWidgetSubItem_28f2b0(a->f40, id, 0));
    if (rows == 0) {
        return 0;
    }
    InvViewCtorFromOwner_3cec70(&filt, w, 5, -1, -1, -1);
    IterInit_370170(&it3, &filt, 0, 0);
    key = ((Area *)((Zone *)w->f08)->f40)->f08;
    i = 0;
    key = key != 0 ? key + 0x88 : key;
    IterInit_370170(&it2, (void *)key, 0, 0);
    memset(a->f0E, -1, 0x10);
    tab = &factory_D_0050CB40[c];
    while ((e = ((Ent *)IterNext_370040(&it2))) != 0) {
        if (e->f02 == 0xB && e->f04 == *tab) {
            n = InvCountById_3c78d0(w->f18, e->f00, 0, 0);
            if (n != 0) {
                rows[i].f08 = n;
                factory_FactoryMaterialGridSetCell_4f33e0(a, b, e->f2C, i, 1);
                a->f0E[i] = e->f03;
                i++;
            }
        }
    }
    UiSetSpriteX_28fcd0(a->f40, (u16)b, -1, i);
    UiSetSubItemX_28f1c0(a->f40, id, -1, i);
    return 1;
}
