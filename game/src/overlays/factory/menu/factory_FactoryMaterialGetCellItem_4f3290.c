/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialGetCellItem_4f3290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    u8  pad00[0x2];
    s8  f02;
    s8  f03;
    s16 f04;
} Ent;

typedef struct Obj {
    u8  pad00[0x4];
    s16 f04;
    u8  pad06[0x4];
    s16 f0A;
    s16 f0C;
} Obj;

typedef struct Slot {
    u8  pad00[0xE];
    s8  f0E;
} Slot;

typedef struct Iter { u8 pad[0x8]; } Iter;

typedef struct World {
    u8    pad00[0x8];
    void *f08;
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

Ent *factory_FactoryMaterialGetCellItem_4f3290(Obj *o)
{
    Iter  it __attribute__((aligned(16)));
    Ent  *e;
    Ent  *r;
    Slot *p;
    s32   key;
    s32   off;
    World *w;

    w = ((World *)GetGameData_1fede0());
    if (w == 0) {
        return 0;
    }
    off = o->f0A + o->f0C * 8;
    key = ((Area *)((Zone *)w->f08)->f40)->f08;
    key = key != 0 ? key + 0x88 : key;
    IterInit_370170(&it, key, 0, 0);
    p = (Slot *)((u8 *)o + off);
    r = 0;
    while ((e = ((Ent *)IterNext_370040(&it))) != 0) {
        if (e->f02 == 0xB && e->f04 == factory_D_0050CB40[o->f04] && e->f03 == p->f0E) {
            r = e;
            break;
        }
    }
    return r;
}
