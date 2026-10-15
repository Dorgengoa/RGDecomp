#include "types.h"

typedef struct Ent { u8 pad00[0x2C]; s16 f2C; } Ent;
typedef struct Meta { u8 pad00[0x16]; s16 f16; u8 pad18[0x2]; s16 f1A; } Meta;
typedef struct Iter { u8 pad00[0x8]; } Iter;

typedef struct Scr {
    u8    pad00[0x74];
    u8    f74[0x14];
    u8    pad88[0x4];
    void *f8C;
    void *f90;
} Scr;

extern void  factory_FactoryPartsSetIcon_4efc40(Scr *o, s16 k, s32 slot);
extern Meta *func_28EA40(void *w, s32 id);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern void  func_36FFF0(Iter *it, s32 n);
extern Ent  *func_36FF80(Iter *it);
extern Ent  *func_370040(Iter *it);
extern void  func_370170(Iter *it, void *p);

void factory_FactoryPartsRefreshIcons_4efc80(Scr *o)
{
    Iter  cur;
    Meta *m;
    Ent  *e;
    s32   n;
    s32   i;

    func_370170(&cur, o->f74);
    func_290010(o->f8C, 0x44, 0, -1);
    m = func_28EA40(o->f90, 0x88F4);
    n = m->f16 + m->f1A;
    if (m->f16 == 3) {
        n -= 3;
    }
    func_36FFF0(&cur, n);
    e = func_36FF80(&cur);
    i = 0;
    while (i <= 3 && e != 0) {
        factory_FactoryPartsSetIcon_4efc40(o, e->f2C, i);
        e = func_370040(&cur);
        i++;
    }
}
