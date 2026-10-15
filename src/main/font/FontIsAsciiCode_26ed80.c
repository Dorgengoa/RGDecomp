#include "types.h"

extern u16 FontGetAsciiCount_26f640(void);

s32 FontIsAsciiCode_26ed80(void *a, s32 k)
{
    if (k != 0xFF02) goto g1;
    return 1;
g1:
    if (k >= 0) goto g2;
    return 0;
g2:
    return k < FontGetAsciiCount_26f640();
}
