#include "types.h"

typedef struct Pair {
    s32 f0;
    s32 f4;
} Pair;

typedef struct Sub {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
} Sub;

typedef struct Hdr {
    u8  pad00[0x4];
    Sub f04;
} Hdr;

typedef struct Ent {
    s16 f00;
    u8  pad02[0x12];
    s16 f14;
    u8  pad16[0x2];
    s16 f18;
} Ent;

typedef struct Scr {
    u8    pad00[0x64];
    void *f64;
    void *f68;
    u8    pad6C[0x8];
    s32   f74;
    u8    f78;
} Scr;

extern Pair D_0050BCE0[];
extern Pair D_0050BD20[];

extern Hdr *func_28EA40(void *w, u32 id);
extern void func_28F670(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F970(void *w, u16 id, s32 x, s32 y, s32 a);
extern void func_28FCD0(void *w, u16 id, s32 v, s32 n);
extern void func_28FD10(void *w, u16 id, s32 x, s32 y, s32 a);
extern Ent *func_28FE10(void *w, u16 id, s32 n);
extern void func_290F50(void *w, u16 id, s32 x, s32 y, s32 a, f32 t);

void factory_FactoryMenuRowHighlight_4f0c80(Scr *o)
{
    Pair  a[8];
    Pair  b[8];
    Pair *s;
    Pair *d;
    Hdr  *h;
    Sub  *m;
    Ent  *e;
    s32   i;

    switch (o->f78) {
    case 0:
        h = func_28EA40(o->f68, 0x88B8);
        m = &h->f04;
        func_28F670(o->f64, 0x18, 0x20, 0x20, 0x20, 0x20, o->f74);
        func_28F670(o->f64, 0x18, 0, 0, 0, 0, m->f12);
        s = D_0050BCE0;
        d = a;
        for (i = 8; i > 0; i--, s++, d++) {
            d->f0 = s->f0;
            d->f4 = s->f4;
        }
        func_28F970(o->f64, 0x19, a[m->f12].f0, a[m->f12].f4, 0);
        s = D_0050BD20;
        d = b;
        for (i = 8; i > 0; i--, s++, d++) {
            d->f0 = s->f0;
            d->f4 = s->f4;
        }
        func_28FD10(o->f64, 0x19, b[m->f12].f0, b[m->f12].f4, 0);
        func_290F50(o->f64, m->f12 + 4, 0xF, 0, 0, 0.5f);
        func_290F50(o->f64, o->f74 + 4, 0, 0, 0, 0.5f);
        func_28F670(o->f64, o->f74 + 4, 0x73, 0x1E, 4, 4, 3);
        func_28F670(o->f64, o->f74 + 4, 0, 0, 0, 0, 4);
        func_28F670(o->f64, m->f12 + 4, 0, 0, 0, 0, 3);
        func_28F670(o->f64, m->f12 + 4, 0x73, 0x1E, 0x4C, 0x18, 4);
        o->f74 = m->f12;
        break;
    case 1:
        if (func_28EA40(o->f68, 0x88C2)->f04.f10 == 0) {
            e = func_28FE10(o->f64, 0x1D, 0);
            func_28FCD0(o->f64, 0x1D, e->f00 + 2, 3);
        } else {
            e = func_28FE10(o->f64, 0x1D, 0);
            func_28FCD0(o->f64, 0x1D, e->f00 + 2 + e->f18, 3);
        }
        break;
    }
}
