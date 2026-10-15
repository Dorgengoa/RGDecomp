#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x26];
    u8  f026;
    u8  f027;
    u8  pad028[0x7C];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern f32  VariantGetFloat_15f740(R8 *q);

s32 DataTableCmdEntrySetParams_41af70(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f026 = VariantGetInt_15f780(src++);
    e->f027 = (s32)(VariantGetFloat_15f740(src));
    return 1;
}
