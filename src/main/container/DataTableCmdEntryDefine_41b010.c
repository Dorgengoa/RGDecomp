#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s32 f004;
    s16 f008;
    u8  b00A_0 : 1;
    u8  pb00A_1 : 7;
    u8  pad00B[0x1];
    s16 f00C;
    u8  pad00E[0x2];
    s16 f010;
    u8  pad012[0x2];
    s32 f014;
    s16 f018;
    u8  pad01A[0x2];
    s32 f01C;
    s16 f020;
    u8  pad022[0x82];
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
extern void * SlotGetInt_15f720(R8 *q);
extern s32  DataTableStoreString_368ab0(Pool *o, void *v);

s32 DataTableCmdEntryDefine_41b010(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    e->f008 = VariantGetInt_15f780(src++);
    SlotGetInt_15f720(src++);
    e->f004 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f020 = VariantGetInt_15f780(src++);
    e->f010 = VariantGetInt_15f780(src++);
    e->f014 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f018 = 0;
    e->f01C = 0;
    e->f002 = VariantGetInt_15f780(src++);
    e->b00A_0 = VariantGetInt_15f780(src++) != 0;
    e->f00C = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
