#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  f000;
    u8  f001;
    u8  f002;
    u8  pad003[0x1];
    s32 f004;
    s32 f008;
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x2];
    s16 cnt002;
    Ent *slots004;
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

s32 DataTableCmdSubEntryDefine_4075b0(R8 *src)
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
    n1 = e0->cnt002;
    i1 = D_00483C78;
    if (i1 >= n1) return 1;
    e = &e0->slots004[i1];
    e->f000 = VariantGetInt_15f780(src);
    e->f001 = 0;
    e->f004 = 0;
    e->f002 = 0;
    e->f008 = 0;
    D_00483C78 = D_00483C78 + 1;
    return 1;
}
