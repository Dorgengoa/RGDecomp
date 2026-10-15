#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x4C];
    s16 f04C[2];
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
extern Ent *AbilityDataGetKind0Rec_3f5db0(Hdr *h);
extern s32  VariantGetInt_15f780(R8 *q);

s32 DataTableCmdEntrySetParams_3f4c40(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = AbilityDataGetKind0Rec_3f5db0(&p->slots[i]);
    if (e == 0) return 1;
    for (k0 = 0; k0 < 0x2; k0++) e->f04C[k0] = VariantGetInt_15f780(src++);
    return 1;
}
