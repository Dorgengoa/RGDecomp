#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0xC];
    u8  b00C_0 : 1;
    u8  b00C_1 : 1;
    u8  b00C_2 : 1;
    u8  b00C_3 : 1;
    u8  b00C_4 : 1;
    u8  b00C_5 : 1;
    u8  b00C_6 : 1;
    u8  b00C_7 : 1;
    u8  pad00D[0x4B];
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

s32 DataTableCmdEntrySetFlags_3fece0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b00C_0 = VariantGetInt_15f780(src++) != 0;
    e->b00C_1 = VariantGetInt_15f780(src++) != 0;
    e->b00C_2 = VariantGetInt_15f780(src++) != 0;
    e->b00C_3 = VariantGetInt_15f780(src++) != 0;
    e->b00C_4 = VariantGetInt_15f780(src++) != 0;
    e->b00C_5 = VariantGetInt_15f780(src++) != 0;
    e->b00C_6 = VariantGetInt_15f780(src++) != 0;
    e->b00C_7 = VariantGetInt_15f780(src) != 0;
    return 1;
}
