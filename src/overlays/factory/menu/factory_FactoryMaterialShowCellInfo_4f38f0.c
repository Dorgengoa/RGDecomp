#include "types.h"

typedef struct Ent {
    u8    pad00[0x2];
    s8    f02;
    s8    f03;
    s16   f04;
    u8    pad06[0x6];
    void *f0C;
    u8    pad10[0x20];
    void *f30;
} Ent;

typedef struct Obj {
    u8    pad00[0x4];
    s16   f04;
    u8    pad06[0x3A];
    void *f40;
    void *f44;
    u8    pad48[0x30];
    u8    f78;
} Obj;

typedef struct Slot {
    u8  pad00[0xE];
    s8  f0E;
} Slot;

typedef struct Sub {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
} Sub;

typedef struct Rec {
    u8  pad00[0x4];
    Sub sub;
} Rec;

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

extern s32 D_0050CB40[];

extern World *func_1FEDE0(void);
extern void   func_370170(Iter *it, s32 key);
extern Ent   *func_370040(Iter *it);
extern void   func_290010(void *h, s32 id, s32 a, s32 b);
extern Rec   *func_28EA40(void *h, s32 id);
extern void   func_28F510(void *h, s32 id, void *p, s32 a);

void factory_FactoryMaterialShowCellInfo_4f38f0(Obj *o)
{
    Iter   it;
    Ent   *e;
    Ent   *r;
    Slot  *p;
    s32    key;
    s32    off;
    World *w;
    Sub   *q;

    if (o->f78 == 2) {
        return;
    }
    func_290010(o->f40, 0x68, 0, -1);
    q = &func_28EA40(o->f44, 0x891C)->sub;
    w = func_1FEDE0();
    if (w == 0) {
        return;
    }
    off = q->f10 + q->f12 * 8;
    key = ((Area *)((Zone *)w->f08)->f40)->f08;
    key = key != 0 ? key + 0x88 : key;
    func_370170(&it, key);
    p = (Slot *)((u8 *)o + off);
    r = 0;
    while ((e = func_370040(&it)) != 0) {
        if (e->f02 == 0xB && e->f04 == D_0050CB40[o->f04] && e->f03 == p->f0E) {
            r = e;
            break;
        }
    }
    if (r != 0) {
        func_290010(o->f40, 0x68, 1, -1);
        func_28F510(o->f40, 0x68, r->f0C, 0);
        func_28F510(o->f40, 0x68, r->f30, 1);
    }
}
