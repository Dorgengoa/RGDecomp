#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8    pad000[0x7C];
    s16   count;
} Pool;

typedef struct G {
    u8   pad000[0x10];
    s16  m10;
    s16  m12;
} G;

extern Pool *D_004830F8;
extern G    *D_00483E44;
extern s32  VariantGetInt_15f780(R8 *q);

s32 DataTableCmdEntryUpdateSetParams_41ce50(R8 *a)
{
    Pool *p = D_004830F8;
    G *g;

    if (p->count <= 0) return 1;
    g = D_00483E44;
    if (g == 0) return 1;
    g->m12 = VariantGetInt_15f780(a++);
    g->m10 = VariantGetInt_15f780(a);
    return 1;
}
