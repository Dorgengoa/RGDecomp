#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x26];
    u8  b026_0 : 1;
    u8  pb026_1 : 7;
    u8  f027;
    u8  f028;
    u8  f029;
    u8  f02A;
    u8  pad02B[0x9];
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

s32 DataTableCmdEntrySetParams_416c80(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b026_0 = VariantGetInt_15f780(src++) != 0;
    e->f027 = VariantGetInt_15f780(src++);
    e->f028 = VariantGetInt_15f780(src++);
    e->f029 = VariantGetInt_15f780(src++);
    e->f02A = VariantGetInt_15f780(src);
    return 1;
}
