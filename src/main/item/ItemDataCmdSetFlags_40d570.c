#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x16];
    u16 b016_0 : 7;
    u16 b016_7 : 5;
    u16 b016_12 : 1;
    u16 b016_13 : 1;
    u16 b016_14 : 1;
    u16 b016_15 : 1;
    u8  b018_0 : 1;
    u8  pb018_1 : 7;
    u8  pad019[0x1B];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32   D_00465B60[3];
extern s32   VariantGetInt_15f780(R8 *q);

s32 ItemDataCmdSetFlags_40d570(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b016_12 = VariantGetInt_15f780(src++);
    e->b016_13 = VariantGetInt_15f780(src++);
    e->b016_14 = VariantGetInt_15f780(src++);
    e->b016_15 = VariantGetInt_15f780(src++);
    e->b016_7 = VariantGetInt_15f780(src++);
    e->b016_0 = VariantGetInt_15f780(src++);
    if (e->b016_14 == 0) e->b016_0 = 1;
    else if (e->b016_0 <= 0) e->b016_0 = D_00465B60[0];
    e->b018_0 = VariantGetInt_15f780(src);
    return 1;
}
