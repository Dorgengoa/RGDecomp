#include "types.h"

typedef struct Ent {
    s16 f00;
} Ent;

typedef struct Rec {
    u8  pad00[0x4];
    Ent *f04;
    u8  pad08[0xC];
    u8  b0 : 1;
    u8  b1 : 1;
} Rec;

typedef struct Hdr {
    u8  pad00[0x12];
    s16 f12;
} Hdr;

typedef union F84 {
    s32 i;
    f32 f;
} F84;

typedef struct Obj {
    u8    pad00[0x6A];
    u8    f6A;
    u8    pad6B[0x19];
    F84   f84;
    void *f88;
    void *f8C;
} Obj;

typedef struct Iter { u8 pad[0x8]; } Iter;

typedef struct World {
    u8    pad00[0x8];
    void *f08;
} World;

typedef struct Zone {
    u8    pad00[0xA4];
    void *fA4;
} Zone;

typedef struct Area {
    u8  pad00[0xC];
    s32 f0C;
} Area;

extern void *D_00484A70;                        /* _gp - 0x700  */
extern u8    D_00480830[1];                     /* _gp - 0x4940 */

extern void *func_28AA30(void *h, s32 id);
extern void  func_28F510(void *h, s32 id, void *p, s32 a);
extern World *func_1FEDE0(void);
extern void  func_370170(Iter *it, s32 key);
extern Rec  *func_370040(Iter *it);
extern f32   func_289710(Obj *o, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void  func_28F970(void *h, s32 a, s32 b, s32 c, s32 d);
extern void  func_290F60(void *h, s32 a, s32 b, s32 c);
extern Hdr  *func_28EA40(void *h, s32 id);

void factory_FactoryHelpTopicListBuild_4f1350(Obj *o)
{
    Iter it;
    Rec *p;
    Rec *e;
    s32  i;
    s32  n;
    s32  key;
    World *w;
    Hdr *h;

    func_28F510(o->f88, 0x80, func_28AA30(D_00484A70, 0x11), 0);
    for (i = 0; i < 9; i++) {
        func_28F510(o->f88, 0x80, func_28AA30(D_00484A70, D_00480830[i] + 0x9C40), i + 1);
    }
    w = func_1FEDE0();
    key = ((Area *)((Zone *)w->f08)->fA4)->f0C;
    if (key != 0) {
        key = key + 0x88;
    }
    func_370170(&it, key);
    e = 0;
    while ((p = func_370040(&it)) != 0) {
        if (p->f04->f00 == 0x418F) {
            e = p;
            break;
        }
    }
    if (e != 0) {
        n = 0xF;
        if (e->b0 != 0) {
            if (e->b1 != 0) {
                n = 0x10;
                o->f6A = 1;
            }
        }
        o->f84.i = 0;
        o->f84.f = func_289710(o, 0x81, 0xED, 9, n, 0);
        func_28F970(o->f88, 0x81, 0x76, 0x56, 0);
        func_28F970(o->f88, 0x81, 0x76, 0x5C, 1);
        func_28F970(o->f88, 0x81, 0x76, 0x64, 2);
        func_290F60(o->f88, 0x81, 0x16C, 0x42);
        h = func_28EA40(o->f8C, 0x8944);
        h->f12 = n - 1;
    }
}
