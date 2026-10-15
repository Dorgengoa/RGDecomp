#include "types.h"

struct T1C6CF0 { u8 pad000[0x14]; s32 f14; u8 pad018[0x10]; s32 f28; s32 f2C; };

extern void MemStackGetStats_14d0e0(struct T1C6CF0 *p, s32 *a, s32 *b, s32 *c, s32 *d);

s32 MemStackGetUsed_1c6cf0(struct T1C6CF0 *p)
{
    s32 v1C;
    s32 v18;
    s32 v14;
    s32 v10;
    u8 t;

    if (p == 0) return 0;
    t = p->f28 != 0;
    if (t) return p->f2C;
    if (p->f14 != 0) goto run;
    return 0;
run:
    MemStackGetStats_14d0e0(p, &v1C, &v18, &v14, &v10);
    return v18;
}
