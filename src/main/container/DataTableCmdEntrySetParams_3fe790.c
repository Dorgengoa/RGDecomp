#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x3A];
    s16 f03A;
    s16 f03C;
    s16 f03E;
    u8  pad040[0x18];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern f32  VariantGetFloat_15f740(R8 *q);
extern s32  VariantGetInt_15f780(R8 *q);
extern const f32 D_0045B078;

s32 DataTableCmdEntrySetParams_3fe790(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    f32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetFloat_15f740(src++);
    e->f03A = (s32)(t0 * D_0045B078);
    e->f03C = VariantGetInt_15f780(src++);
    VariantGetInt_15f780(src++);
    e->f03E = VariantGetInt_15f780(src);
    return 1;
}
