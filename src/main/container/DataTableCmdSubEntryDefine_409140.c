#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x12];
    s16 f014;
    s16 f016;
    u8  b018_0 : 1;
    u8  pb018_1 : 7;
    u8  pad019[0x3];
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x4];
    s16 cnt004;
    u8  pad006[0x2];
    Ent *slots008;
    u8  pad00C[0xC];
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
extern s32  D_00480230;

s32 DataTableCmdSubEntryDefine_409140(R8 *src)
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
    n1 = e0->cnt004;
    i1 = D_00480230;
    if (i1 >= n1) return 1;
    e = &e0->slots008[i1];
    e->f000 = VariantGetInt_15f780(src++);
    e->b018_0 = VariantGetInt_15f780(src) != 0;
    e->f014 = 0xA;
    e->f016 = -1;
    D_00480230 = D_00480230 + 1;
    return 1;
}
