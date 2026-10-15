#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s16 f004;
    s16 f006;
    s16 f008;
    u8  pad00A[0xA];
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

s32 DataTableCmdEntryDefine_3fa2b0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  t4;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    SlotGetInt_15f720(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->f006 = VariantGetInt_15f780(src++);
    t4 = VariantGetInt_15f780(src++);
    while (t4 > 0) { e->f008 = VariantGetInt_15f780(src); break; }
    D_004830FC = D_004830FC + 1;
    return 1;
}
