#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x1C];
    s16 f01C[6];
} Ent;

typedef struct Lvl1 {
    u8  pad000[0x12];
    s16 cnt012;
    Ent *slots014;
} Lvl1;
typedef struct Lvl0 {
    u8  pad000[0xE];
    s16 cnt00E;
    Lvl1 *slots010;
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x4];
    s32  m094;
    s32  m098;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);

s32 DataTableCmdSubEntrySetIntArray_40b5d0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    Lvl1 *e1;
    s32   n2;
    Ent  *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt00E;
    if (p->m094 - 1 >= n1) return 1;
    e1 = &e0->slots010[p->m094] - 1;
    n2 = e1->cnt012;
    if (p->m098 - 1 >= n2) return 1;
    e = &e1->slots014[p->m098] - 1;
    for (k0 = 0; k0 < 0x6; k0++) e->f01C[k0] = VariantGetInt_15f780(src++);
    return 1;
}
