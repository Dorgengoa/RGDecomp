#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0xC];
    s16 f00C;
    s16 f00E;
    s16 f010;
    s16 f012;
    u8  pad014[0x1A];
    s16 f02E;
    u8  pad030[0x14];
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
extern const f32 D_0045B078;

s32 DataTableCmdEntrySetParams_4278a0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    f32  t4;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f00C = VariantGetInt_15f780(src++);
    e->f00E = VariantGetInt_15f780(src++);
    e->f010 = VariantGetInt_15f780(src++);
    e->f012 = VariantGetInt_15f780(src++);
    t4 = VariantGetFloat_15f740(src);
    e->f02E = (s32)(t4 * D_0045B078);
    return 1;
}
