#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x20];
    s32 f020;
    s32 f024;
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
extern void * SlotGetInt_15f720(R8 *q);
extern s32  DataTableStoreString_368ab0(Pool *o, void *v);

s32 DataTableCmdEntrySetString_4011d0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f020 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f024 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f028 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src));
    return 1;
}
