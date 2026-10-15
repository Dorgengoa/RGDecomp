#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
} Ent;

typedef struct Hdr { u8 b[0x1C]; } Hdr;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Hdr *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern Ent *AbilityDataGetKind1Rec_3f5de0(Hdr *h);
extern s32  VariantGetInt_15f780(R8 *q);

s32 DataTableCmdEntrySetParams_3f5360(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = AbilityDataGetKind1Rec_3f5de0(&p->slots[i]);
    if (e == 0) return 1;
    e->f000 = VariantGetInt_15f780(src++);
    e->f002 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->f006 = VariantGetInt_15f780(src);
    return 1;
}
