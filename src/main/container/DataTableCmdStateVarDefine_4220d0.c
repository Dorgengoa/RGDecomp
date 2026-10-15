#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s32 f004;
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0x4];
    s32  m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32   VariantGetInt_15f780(R8 *q);
extern s8   *SlotGetInt_15f720(R8 *q);
extern s32   DataTableStoreString_368ab0(Pool *o, void *v);
extern void  StateVarSetQuiet_3cca20(s32 h, s32 a, s32 b);

s32 DataTableCmdStateVarDefine_4220d0(R8 *src)
{
    Pool *p = D_004830F8;
    s32   t0;
    s8   *t1;
    s32   t2;
    s32   n;
    s32   i;
    Ent  *e;

    t0 = VariantGetInt_15f780(src++);
    t1 = SlotGetInt_15f720(src++);
    t2 = VariantGetInt_15f780(src);
    if (p->m094 != 0) StateVarSetQuiet_3cca20(p->m094, t0, (s16)t2);
    if (t0 < 0 || t0 >= 0x80) return 1;
    if (t1 == 0) return 1;
    if (*t1 == 0) return 1;
    if (p->slots == 0) return 1;
    n = p->count;
    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = t0;
    e->f004 = DataTableStoreString_368ab0(p, t1);
    D_004830FC = D_004830FC + 1;
    return 1;
}
