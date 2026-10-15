#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x14];
    f32 f014;
    f32 f018;
    f32 f01C;
    u8  pad020[0x14];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern f32  VariantGetFloat_15f740(R8 *q);

s32 DataTableCmdEntrySetParams_400e30(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f014 = VariantGetFloat_15f740(src++);
    e->f018 = VariantGetFloat_15f740(src++);
    e->f01C = VariantGetFloat_15f740(src);
    return 1;
}
