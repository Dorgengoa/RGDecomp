#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Rec0 {
    u8  a000;
    u8  a001;
} Rec0;

typedef struct Ent {
    u8  pad000[0x4];
    s16 f004;
    u8  pad006[0x2];
    s16 f008;
    s16 f00A;
    u8  f00C;
    u8  f00D;
    u8  f00E;
    u8  f00F;
    Rec0 f010[6];
    s16 f01C;
    s16 f01E;
    s16 f020[3];
    s16 f026[3];
} Ent;

typedef struct Hdr { u8 b[0x34]; } Hdr;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Hdr *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern Ent *ItemDefGetInsectData_40e0b0(Hdr *h);
extern s32  VariantGetInt_15f780(R8 *q);

s32 ItemDataCmdInsectSetParams_40ca00(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;
    s32  k1;
    s32  k2;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = ItemDefGetInsectData_40e0b0(&p->slots[i]);
    if (e == 0) return 1;
    e->f004 = VariantGetInt_15f780(src++);
    e->f008 = VariantGetInt_15f780(src++);
    e->f00A = VariantGetInt_15f780(src++);
    e->f00C = VariantGetInt_15f780(src++);
    e->f00D = VariantGetInt_15f780(src++);
    e->f00E = VariantGetInt_15f780(src++);
    e->f00F = VariantGetInt_15f780(src++);
    for (k0 = 0; k0 < 0x6; k0++) {
        e->f010[k0].a000 = VariantGetInt_15f780(src++);
        e->f010[k0].a001 = VariantGetInt_15f780(src++);
    }
    e->f01C = VariantGetInt_15f780(src++);
    e->f01E = VariantGetInt_15f780(src++);
    for (k1 = 0; k1 < 0x3; k1++) e->f020[k1] = VariantGetInt_15f780(src++);
    for (k2 = 0; k2 < 0x3; k2++) e->f026[k2] = VariantGetInt_15f780(src++);
    return 1;
}
