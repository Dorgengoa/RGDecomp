#include "types.h"

typedef struct Pt {
    s16 f00;
    s16 f02;
    u16 f04;
} Pt;

typedef struct Ctx {
    u8  pad00[0x64];
    s32 f64;
} Ctx;

extern s32 factory_FactoryGridDirDx_4ff9f0(s32 dir);
extern s32 factory_FactoryGridDirDy_4ff9b0(s32 dir);
extern s32 factory_FactoryPartDefPathStart_4fe410(Ctx *a, Pt *t, void *c, void *d, s32 i);

s32 factory_FactoryPartDefFindPathFrom_4fe290(Ctx *a, Pt *b, void *c, void *d)
{
    Pt  t;
    s32 x;
    s32 i;
    s32 y;

    if (b == 0 || c == 0) {
        return -1;
    }
    x = b->f00 + factory_FactoryGridDirDx_4ff9f0(b->f04 & 3);
    y = b->f02 + factory_FactoryGridDirDy_4ff9b0(b->f04 & 3);
    for (i = 0; i < a->f64; i++) {
        if (factory_FactoryPartDefPathStart_4fe410(a, &t, c, d, i) != 0) {
            if (t.f00 == x && t.f02 == y && (t.f04 & 3) == (b->f04 & 3)) {
                return i;
            }
        }
    }
    return -1;
}
