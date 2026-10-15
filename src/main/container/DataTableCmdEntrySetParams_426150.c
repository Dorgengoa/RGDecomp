#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x18];
    s16 f018;
    u8  b01A_0 : 1;
    u8  pb01A_1 : 7;
    u8  pad01B[0x1];
    s32 f01C;
    f32 f020;
    f32 f024;
    f32 f028;
    f32 f02C;
    s32 f030;
    s32 f034;
    u8  pad038[0xC];
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
extern void * SlotGetInt_15f720(R8 *q);
extern s32  DataTableStoreString_368ab0(Pool *o, void *v);
extern f32  VariantGetFloat_15f740(R8 *q);

s32 DataTableCmdEntrySetParams_426150(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    VariantGetInt_15f780(src++);
    e->b01A_0 = VariantGetInt_15f780(src++) != 0;
    e->f018 = VariantGetInt_15f780(src++);
    e->f01C = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f020 = VariantGetFloat_15f740(src++);
    e->f024 = VariantGetFloat_15f740(src++);
    e->f028 = VariantGetFloat_15f740(src++);
    e->f030 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f034 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f02C = VariantGetFloat_15f740(src);
    return 1;
}
