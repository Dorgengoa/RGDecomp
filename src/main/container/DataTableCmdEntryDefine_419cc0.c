#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    u8  f004;
    u8  f005;
    u8  f006;
    u8  f007;
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
extern void SlotGetInt_15f720(R8 *q);

s32 DataTableCmdEntryDefine_419cc0(R8 *src)
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
    e->f005 = VariantGetInt_15f780(src++);
    e->f006 = VariantGetInt_15f780(src++);
    e->f007 = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
