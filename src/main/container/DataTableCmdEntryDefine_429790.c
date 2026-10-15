#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    u8  pad006[0x2];
    s32 f008;
    s32 f00C;
    s32 f010;
    u8  f014;
    u8  pad015[0x3];
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
extern s32  DataTableHashName_368a10(Pool *o, s32 v);
extern s32  DataTableBitsetClaim_3688b0(Pool *o, s32 v);

s32 DataTableCmdEntryDefine_429790(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  t2;
    s32  t3;
    s32  t5;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    t2 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f008 = t2;
    t3 = DataTableHashName_368a10(p, t2);
    e->f002 = t3;
    DataTableBitsetClaim_3688b0(p, (u16)t3);
    e->f004 = VariantGetInt_15f780(src++);
    t5 = VariantGetInt_15f780(src) != 0;
    switch (e->f004) {
    case 1:
        e->f00C = 0;
        break;
    case 2:
        e->f00C = 0;
        e->f010 = 0;
        e->f014 = t5;
        break;
    case 3:
        e->f00C = 0;
        e->f010 = 0;
        break;
    }
    D_004830FC = D_004830FC + 1;
    return 1;
}
