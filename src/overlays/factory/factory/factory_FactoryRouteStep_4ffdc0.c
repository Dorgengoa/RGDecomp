#include "types.h"

typedef struct Pt3 {
    s16 f0;
    s16 f2;
    s16 f4;
} Pt3;

typedef struct Box {
    s16 f0;
    s16 f2;
    u16 f4;
} Box;

typedef struct Ent {
    u8 pad00[0x26];
    s8 f26;
    u8 pad27[0x9];
    u8 f30;
} Ent;

extern void *factory_FactoryPartGroupFindById_504080(void *a, s32 id);
extern Ent  *factory_FactoryPartGroupGetObj_4fea80(void *h, s32 id);
extern s32   factory_FactoryPartDefPathEnd_4fe3a0(void *h, Box *b, u8 *p, s32 c, s32 d);
extern s32   factory_FactoryPartDefFindPathFrom_4fe290(void *h, Box *b, u8 *p, s32 c);
extern s32   factory_FactoryGridDirDx_4ff9f0(s32 t);
extern s32   factory_FactoryGridDirDy_4ff9b0(s32 t);
extern Pt3  *factory_FactoryGridCellAt_5037f0(void *a, s32 x, s32 y);

s32 factory_FactoryRouteStep_4ffdc0(void *a, Pt3 *b, Pt3 *c)
{
    Box v;
    void *h;
    Ent *e;
    Pt3 *p;
    s32 x;
    s32 y;
    s32 r;

    if (b == 0 || c == 0) {
        return 0;
    }
    h = factory_FactoryPartGroupFindById_504080(a, c->f0);
    if (h == 0) {
        return 0;
    }
    e = factory_FactoryPartGroupGetObj_4fea80(h, c->f2);
    if (e == 0) {
        return 0;
    }
    if (factory_FactoryPartDefPathEnd_4fe3a0(h, &v, &e->f30, e->f26, c->f4) == 0) {
        return 0;
    }
    x = v.f0 + factory_FactoryGridDirDx_4ff9f0(v.f4);
    y = v.f2 + factory_FactoryGridDirDy_4ff9b0(v.f4);
    p = factory_FactoryGridCellAt_5037f0(a, x, y);
    if (p == 0) {
        return 0;
    }
    h = factory_FactoryPartGroupFindById_504080(a, p->f0);
    if (h == 0) {
        return 0;
    }
    e = factory_FactoryPartGroupGetObj_4fea80(h, p->f2);
    if (e == 0) {
        return 0;
    }
    r = factory_FactoryPartDefFindPathFrom_4fe290(h, &v, &e->f30, e->f26);
    b->f4 = r;
    if ((s16)r < 0) {
        return 0;
    }
    b->f0 = p->f0;
    b->f2 = p->f2;
    return 1;
}
