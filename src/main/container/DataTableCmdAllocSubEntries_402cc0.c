#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x7C];
    s16 pb07C_0 : 5;
    s16 b07C_5 : 5;
    s16 pb07C_10 : 6;
    u8  pad07E[0x6];
    s32 f084;
    u8  pad088[0x8];
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0x8];
    s32  m098;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern s32  ArenaNew_4049f0(s32 a, void *b, s32 c, s32 d);

s32 DataTableCmdAllocSubEntries_402cc0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b07C_5 = (s16)VariantGetInt_15f780(src);
    if ((s16)(s32)e->b07C_5 > 0) e->f084 = ArenaNew_4049f0((s16)(s32)e->b07C_5 * 0x4, p->m6C, 0x4, -1);
    else e->f084 = 0;
    p->m098 = 0;
    return 1;
}
