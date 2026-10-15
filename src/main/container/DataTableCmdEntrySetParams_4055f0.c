#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x10];
    s16 f010;
    u8  pad012[0x2];
    f32 f014;
    f32 f018;
    f32 f01C;
    f32 f020;
    f32 f024;
    f32 f028;
    f32 f02C;
    f32 f030;
    f32 f034;
    f32 f038;
    f32 f03C;
    f32 f040;
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

s32 DataTableCmdEntrySetParams_4055f0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f010 = VariantGetInt_15f780(src++);
    VariantGetInt_15f780(src++);
    VariantGetFloat_15f740(src++);
    VariantGetFloat_15f740(src++);
    VariantGetFloat_15f740(src++);
    VariantGetInt_15f780(src++);
    VariantGetFloat_15f740(src++);
    VariantGetFloat_15f740(src++);
    VariantGetFloat_15f740(src++);
    VariantGetInt_15f780(src++);
    VariantGetFloat_15f740(src++);
    VariantGetFloat_15f740(src++);
    VariantGetFloat_15f740(src++);
    e->f014 = VariantGetFloat_15f740(src++);
    e->f018 = VariantGetFloat_15f740(src++);
    e->f01C = VariantGetFloat_15f740(src++);
    e->f020 = VariantGetFloat_15f740(src++);
    e->f024 = VariantGetFloat_15f740(src++);
    e->f028 = VariantGetFloat_15f740(src++);
    e->f02C = VariantGetFloat_15f740(src++);
    e->f030 = VariantGetFloat_15f740(src++);
    e->f034 = VariantGetFloat_15f740(src++);
    e->f038 = VariantGetFloat_15f740(src++);
    e->f03C = VariantGetFloat_15f740(src++);
    e->f040 = VariantGetFloat_15f740(src);
    return 1;
}
