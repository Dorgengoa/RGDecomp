#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s32 f004;
    s16 f008;
    u8  pad00A[0x2];
    s16 f00C;
    u8  pad00E[0x2];
    s16 f010;
    u8  pad012[0x6];
} Ent;

typedef struct Lvl0 {
    u8  pad000[0xE];
    s16 cnt00E;
    Ent *slots010;
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x4];
    s32  m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern void * SlotGetInt_15f720(R8 *q);
extern s32  DataTableStoreString_368ab0(Pool *o, void *v);

s32 DataTableCmdSubEntryDefine_40ba80(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    s32   i1;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt00E;
    i1 = p->m094;
    if (i1 >= n1) return 1;
    e = &e0->slots010[i1];
    e->f000 = VariantGetInt_15f780(src++);
    e->f002 = VariantGetInt_15f780(src++);
    e->f004 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f008 = VariantGetInt_15f780(src++);
    e->f00C = VariantGetInt_15f780(src++);
    e->f010 = VariantGetInt_15f780(src);
    p->m094 = p->m094 + 1;
    return 1;
}
