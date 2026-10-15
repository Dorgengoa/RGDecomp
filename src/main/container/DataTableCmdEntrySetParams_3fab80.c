#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x1C];
    u8  b01C_0 : 5;
    u8  b01C_5 : 3;
    u8  pad01D[0x13];
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
extern void SlotGetInt_15f720(R8 *q);

s32 DataTableCmdEntrySetParams_3fab80(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b01C_0 = VariantGetInt_15f780(src++);
    e->b01C_5 = VariantGetInt_15f780(src++);
    SlotGetInt_15f720(src);
    return 1;
}
