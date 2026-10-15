#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  f000;
    u8  f001;
    u8  f002;
    u8  b003_0 : 4;
    u8  b003_4 : 1;
    u8  pb003_5 : 3;
    s16 f004;
} Ent;

typedef struct Lvl1 {
    u8  pad000[0x1];
    u8  cnt001;
    u8  pad002[0x2];
    Ent *slots004;
    u8  pad008[0x4];
} Lvl1;
typedef struct Lvl0 {
    u8  pad000[0x2];
    s16 cnt002;
    Lvl1 *slots004;
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
extern u8   D_00483C78;
extern u8   D_00483C7C;

s32 DataTableCmdSubEntryDefine_407370(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    Lvl1 *e1;
    s32   n2;
    s32   i2;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt002;
    if (D_00483C78 - 1 >= n1) return 1;
    e1 = &e0->slots004[D_00483C78] - 1;
    n2 = e1->cnt001;
    i2 = D_00483C7C;
    if (i2 >= n2) return 1;
    e = &e1->slots004[i2];
    e->f000 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->b003_4 = VariantGetInt_15f780(src++);
    e->b003_0 = VariantGetInt_15f780(src++);
    e->f002 = VariantGetInt_15f780(src++);
    e->f001 = VariantGetInt_15f780(src);
    D_00483C7C = D_00483C7C + 1;
    return 1;
}
