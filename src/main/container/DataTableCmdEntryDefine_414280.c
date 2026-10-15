#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s32 f004;
    s32 f008;
    u8  pad00C[0xC];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0x8];
    s16  m098;
    s16  m09A;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern void * SlotGetInt_15f720(R8 *q);
extern s32  DataTableStoreString_368ab0(Pool *o, void *v);

s32 DataTableCmdEntryDefine_414280(R8 *src)
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
    if (p->m098 < 0 || e->f000 < p->m098) p->m098 = e->f000;
    if (p->m09A < 0 || p->m09A < e->f000) p->m09A = e->f000;
    e->f004 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f008 = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
