#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s32 f004[468];
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
extern void RevelationBoardCellReset_409e30(s32 *q);

s32 DataTableCmdEntryDefine_408a90(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32 *qp0;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src);
    qp0 = e->f004;
    for (k0 = 0; k0 < 0x1D4; k0++) {
        RevelationBoardCellReset_409e30(qp0);
        qp0++;
    }
    D_004830FC = D_004830FC + 1;
    return 1;
}
