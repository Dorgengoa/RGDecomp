#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x2];
    u8  b002_0 : 1;
    u8  pb002_1 : 7;
    u8  pad003[0x9];
    s32 f00C[2];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern void * SlotGetInt_15f720(R8 *q);
extern s32  DataTableStoreString_368ab0(Pool *o, void *v);
extern s32  VariantGetInt_15f780(R8 *q);

s32 DataTableCmdEntrySetParams_3fa1d0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    for (k0 = 0; k0 < 0x2; k0++) e->f00C[k0] = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->b002_0 = VariantGetInt_15f780(src) != 0;
    return 1;
}
