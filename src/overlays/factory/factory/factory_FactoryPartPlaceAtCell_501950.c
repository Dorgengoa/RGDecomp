#include "types.h"

typedef struct H {
    u8  pad00[0xA];
    s16 f0A;
    s16 f0C;
    u8  pad0E[0x6];
    s8  f14;
    s8  f15;
} H;

extern H  *factory_FactoryPartGroupFindById_504080(void *a);
extern f32 factory_FactoryGridCellCenterX_503760(void *a, s32 v);
extern f32 factory_FactoryGridCellCenterZ_503730(void *a, s32 v);
extern s32 factory_FactoryPartPlace_5013f0(void *a, void *b, s32 e, f32 x, f32 y);

s32 factory_FactoryPartPlaceAtCell_501950(void *a, void *b, s32 c, s32 d, s32 e)
{
    H  *h;
    s32 m;
    s32 n;
    s32 v;
    s32 sgn;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;

    h = factory_FactoryPartGroupFindById_504080(a);
    if (h == 0) {
        return 0;
    }
    if (h->f0A <= h->f0C) {
        return 0;
    }
    x0 = factory_FactoryGridCellCenterX_503760(a, c);
    y0 = factory_FactoryGridCellCenterZ_503730(a, d);
    m = e & 1;
    v = (s8)(m != 0 ? h->f15 : h->f14);
    n = e & 2;
    sgn = n != 0 ? -1 : 1;
    x1 = factory_FactoryGridCellCenterX_503760(a, c + sgn * (v - 1));
    v = (s8)(m != 0 ? h->f14 : h->f15);
    sgn = n != 0 ? -1 : 1;
    y1 = factory_FactoryGridCellCenterZ_503730(a, d + sgn * (v - 1));
    return factory_FactoryPartPlace_5013f0(a, b, e, 0.5f * (x0 + x1), 0.5f * (y0 + y1));
}
