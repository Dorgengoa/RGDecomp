#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x14];
    u8  b014_0 : 4;
    u8  b014_4 : 4;
    u8  b015_0 : 7;
    u8  pb015_7 : 1;
    u8  pad016[0xA];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);

s32 DataTableCmdEntrySetParams_4045a0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b014_0 = VariantGetInt_15f780(src++);
    e->b015_0 = VariantGetInt_15f780(src++);
    e->b014_4 = VariantGetInt_15f780(src);
    return 1;
}
