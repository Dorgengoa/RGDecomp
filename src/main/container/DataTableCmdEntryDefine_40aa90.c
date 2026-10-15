#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  b002_0 : 1;
    u8  pb002_1 : 7;
    u8  pad003[0x1];
    s16 f004;
    u8  pad006[0x2];
    s32 f008;
    s32 f00C;
    s32 f010;
    u8  pad014[0x4];
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

s32 DataTableCmdEntryDefine_40aa90(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    Ent *e;
    s32  t0;

    if (n <= 0) return 1;
    if (D_004830FC >= n) return 1;
    t0 = VariantGetInt_15f780(src++);
    e = &p->slots[D_004830FC];
    e->f000 = t0;
    SlotGetInt_15f720(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->f008 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f00C = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f010 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->b002_0 = VariantGetInt_15f780(src) != 0;
    D_004830FC = D_004830FC + 1;
    return 1;
}
