#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x81];
    u8  pb081_0 : 3;
    u8  b081_3 : 1;
    u8  b081_4 : 1;
    u8  b081_5 : 1;
    u8  b081_6 : 1;
    u8  b081_7 : 1;
    u8  b082_0 : 1;
    u8  b082_1 : 1;
    u8  b082_2 : 1;
    u8  b082_3 : 1;
    u8  b082_4 : 1;
    u8  pb082_5 : 3;
    u8  pad083[0x21];
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

s32 DataTableCmdEntrySetFlags_41a540(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b081_3 = VariantGetInt_15f780(src++) != 0;
    e->b081_4 = VariantGetInt_15f780(src++) != 0;
    e->b081_5 = VariantGetInt_15f780(src++) != 0;
    e->b081_6 = VariantGetInt_15f780(src++) != 0;
    e->b081_7 = VariantGetInt_15f780(src++) != 0;
    e->b082_0 = VariantGetInt_15f780(src++) != 0;
    e->b082_1 = VariantGetInt_15f780(src++) != 0;
    e->b082_2 = VariantGetInt_15f780(src++) != 0;
    e->b082_3 = VariantGetInt_15f780(src++) != 0;
    e->b082_4 = VariantGetInt_15f780(src) != 0;
    return 1;
}
