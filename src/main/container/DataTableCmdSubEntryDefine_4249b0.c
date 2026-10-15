#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    u8  b006_0 : 1;
    u8  pb006_1 : 7;
    u8  pad007[0x5];
} Ent;

typedef struct Lvl0 {
    u8  pad000[0xA];
    s16 cnt00A;
    Ent *slots00C;
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
extern s32  D_00483F10;
extern u8   D_00483F14;

s32 DataTableCmdSubEntryDefine_4249b0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n;
    s32 i;
    Lvl0 *e0;
    Ent *q1;
    s32   n1;
    s32   i1;
    Ent  *e;

    if (D_00483F14 != 0) return 1;
    n = p->count;
    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    q1 = e0->slots00C;
    if (q1 == 0) return 1;
    n1 = e0->cnt00A;
    if (n1 <= 0) return 1;
    i1 = D_00483F10;
    if (i1 >= n1) return 1;
    e = &q1[i1];
    e->f000 = VariantGetInt_15f780(src++);
    e->f002 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->b006_0 = VariantGetInt_15f780(src);
    D_00483F10 = D_00483F10 + 1;
    return 1;
}
