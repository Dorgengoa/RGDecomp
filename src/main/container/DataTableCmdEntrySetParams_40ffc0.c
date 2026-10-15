#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0xF];
    u8  b00F_0 : 1;
    u8  pb00F_1 : 7;
    u8  pad010[0x18];
    s16 f028;
    s16 f02A;
    s16 f02C;
    s16 f02E;
    f32 f030;
    f32 f034;
    f32 f038;
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

s32 DataTableCmdEntrySetParams_40ffc0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    f32  t3;
    f32  t5;
    f32  t8;
    f32  t10;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b00F_0 = VariantGetInt_15f780(src++) != 0;
    e->f028 = VariantGetInt_15f780(src++);
    e->f02A = VariantGetInt_15f780(src++);
    t3 = VariantGetFloat_15f740(src++);
    e->f030 = t3 * D_0045B078;
    t5 = VariantGetFloat_15f740(src++);
    e->f02E = t5 * D_0045B078;
    e->f02C = VariantGetInt_15f780(src++);
    t8 = VariantGetFloat_15f740(src++);
    e->f034 = t8 * D_0045B078;
    t10 = VariantGetFloat_15f740(src);
    e->f038 = t10 * D_0045B078;
    return 1;
}
