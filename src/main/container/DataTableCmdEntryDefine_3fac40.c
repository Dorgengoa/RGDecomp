#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Rec0 {
    s16 a000;
    u8  pad002[0x2];
} Rec0;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x6];
    s16 f008;
    u8  pad00A[0x2];
    s16 f00C;
    u8  pad00E[0x2];
    Rec0 f010[3];
    u8  pad01C[0x8];
    s16 f024;
    u8  pad026[0x2];
    s32 f028;
    u8  pad02C[0x4];
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
extern void SlotGetInt_15f720(R8 *q);

s32 DataTableCmdEntryDefine_3fac40(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f024 = 0;
    e->f028 = 0;
    e->f000 = VariantGetInt_15f780(src++);
    SlotGetInt_15f720(src++);
    e->f008 = VariantGetInt_15f780(src++);
    for (k0 = 0; k0 < 0x3; k0++) e->f010[k0].a000 = VariantGetInt_15f780(src++);
    VariantGetInt_15f780(src++);
    e->f00C = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
