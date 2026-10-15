#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x6];
    s16 f008;
    u8  pad00A[0x2];
    s32 f00C;
    s32 f010;
    s32 f014;
    s32 f018;
    s32 f01C;
    s32 f020;
    u8  pad024[0x4];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0x4];
    s32  m094;
    s32  m098;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern s32  DataTableStoreString_368ab0(Pool *o, void *v);
extern s8   *SlotGetInt_15f720(R8 *q);

s32 DataTableCmdEntryDefine_4161f0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n;
    s32 i;
    Ent *e;
    s32  t0;
    s32  m0;
    s8  * t1;
    s8  * t2;
    s8  * t3;
    s8  * t4;

    t0 = VariantGetInt_15f780(src++);
    m0 = p->m098;
    t1 = SlotGetInt_15f720(src++);
    t2 = SlotGetInt_15f720(src++);
    t3 = SlotGetInt_15f720(src++);
    t4 = SlotGetInt_15f720(src);
    if (m0 < 0 || m0 >= 0xB) return 1;
    if (t2 == 0) return 1;
    if (*t2 == 0) return 1;
    if (p->slots == 0) return 1;
    n = p->count;
    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f01C = 0;
    e->f020 = 0;
    e->f000 = t0;
    e->f008 = m0;
    e->f00C = DataTableStoreString_368ab0(p, t1);
    e->f010 = DataTableStoreString_368ab0(p, t2);
    e->f014 = DataTableStoreString_368ab0(p, t3);
    e->f018 = DataTableStoreString_368ab0(p, t4);
    D_004830FC = D_004830FC + 1;
    p->m094 = 0;
    p->m098 = p->m098 + 1;
    return 1;
}
