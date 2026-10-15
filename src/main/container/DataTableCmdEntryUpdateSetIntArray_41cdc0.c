#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8    pad000[0x7C];
    s16   count;
} Pool;

typedef struct G {
    u8   pad000[0x1C];
    s16  m1C[5];
} G;

extern Pool *D_004830F8;
extern G    *D_00483E44;
extern s32  VariantGetInt_15f780(R8 *q);

s32 DataTableCmdEntryUpdateSetIntArray_41cdc0(R8 *a)
{
    Pool *p = D_004830F8;
    G *g;
    s32 i;

    if (p->count <= 0) return 1;
    g = D_00483E44;
    if (g == 0) return 1;
    VariantGetInt_15f780(a++);
    for (i = 0; i < 5; i++) {
        g->m1C[i] = VariantGetInt_15f780(a++);
    }
    return 1;
}
