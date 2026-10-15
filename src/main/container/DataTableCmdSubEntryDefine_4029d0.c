#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x7D];
    s8  pb07D_0 : 2;
    s8  b07D_2 : 6;
    u8  pad07E[0xA];
    Ent *slots088;
    u8  pad08C[0x4];
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0xC];
    s32  m09C;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32   VariantGetInt_15f780(R8 *q);

s32 DataTableCmdSubEntryDefine_4029d0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    Ent *q1;
    s32   n1;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    q1 = e0->slots088;
    if (q1 == 0) return 1;
    n1 = (s8)(s32)e0->b07D_2;
    if (n1 <= 0) return 1;
    if (p->m09C - 1 >= n1) return 1;
    e = &q1[p->m09C];
    e = (Ent *)(s32)e;
    e->f000 = VariantGetInt_15f780(src);
    p->m09C = p->m09C + 1;
    return 1;
}
