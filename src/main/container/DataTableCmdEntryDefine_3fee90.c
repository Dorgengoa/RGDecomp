#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  f002;
    u8  f003;
    u8  pad004[0x4];
    s32 f008;
    u8  pad00C[0x4C];
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

s32 DataTableCmdEntryDefine_3fee90(R8 *src)
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
    e->f008 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f002 = VariantGetInt_15f780(src++);
    e->f003 = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
