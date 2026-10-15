#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  f000;
    u8  pad001[0x1];
    s16 f002;
    u8  f004;
    u8  f005;
    u8  f006;
    u8  f007[6];
    u8  pad00D[0x1];
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x4];
    Ent *slots004;
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x4];
    s32  m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);

s32 DataTableCmdSubEntryAdd_3f6f30(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    Ent  *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    e = &e0->slots004[p->m094];
    e->f000 = VariantGetInt_15f780(src++);
    e->f002 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->f005 = VariantGetInt_15f780(src++);
    e->f006 = VariantGetInt_15f780(src++);
    for (k0 = 0; k0 < 0x6; k0++) e->f007[k0] = VariantGetInt_15f780(src++);
    p->m094 = p->m094 + 1;
    return 1;
}
