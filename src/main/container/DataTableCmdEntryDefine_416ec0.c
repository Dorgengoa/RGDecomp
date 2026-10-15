#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s32 f004;
    s32 f008;
    s32 f00C;
    u8  pad010[0xC];
    s32 f01C;
    u8  pad020[0x14];
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
extern s32  ParseMemOrderKeyword_1ecb40(void *v);
extern s32  ParseFncSpaceKeyword_1ecb00(void *v);

s32 DataTableCmdEntryDefine_416ec0(R8 *src)
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
    e->f004 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    t4 = ParseMemOrderKeyword_1ecb40(SlotGetInt_15f720(src++));
    e->f008 = t4 | ParseFncSpaceKeyword_1ecb00(SlotGetInt_15f720(src++));
    e->f00C = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f01C = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src));
    D_004830FC = D_004830FC + 1;
    return 1;
}
