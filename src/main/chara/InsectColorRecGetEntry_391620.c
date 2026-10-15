#include "types.h"

extern u8 *InsectColorRecFindById_391680(void *p);

u8 *InsectColorRecGetEntry_391620(void *p, s32 i)
{
    u8 *q;

    q = InsectColorRecFindById_391680(p);
    if (q != 0) goto g1;
    return 0;
g1:
    if (i >= 0) goto g2;
    return 0;
g2:
    if (i < 9) goto g3;
    return 0;
g3:
    return q + i * 16 + 4;
}
