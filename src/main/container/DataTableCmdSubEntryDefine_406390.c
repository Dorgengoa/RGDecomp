#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s16 f004;
    u8  pad006[0xA];
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x8];
    s16 cnt008;
    u8  pad00A[0x2];
    Ent *slots00C;
    u8  pad010[0x8];
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern s32  D_00483C4C;

s32 DataTableCmdSubEntryDefine_406390(R8 *src)
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
    n1 = e0->cnt008;
    i1 = D_00483C4C;
    if (i1 >= n1) return 1;
    e = &e0->slots00C[i1];
    e->f000 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src);
    D_00483C4C = D_00483C4C + 1;
    return 1;
}
