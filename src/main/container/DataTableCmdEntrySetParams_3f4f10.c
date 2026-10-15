#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0xC];
    s32 f00C;
    s16 f010;
    u8  pad012[0x2];
    s16 f014;
    u8  pad016[0x12];
    f32 f028;
    u8  pad02C[0x10];
    s16 f03C;
    s16 f03E;
    u8  pad040[0x4];
    s16 f044;
    s16 f046;
} Ent;

typedef struct Hdr { u8 b[0x1C]; } Hdr;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Hdr *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern Ent *AbilityDataGetKind0Rec_3f5db0(Hdr *h);
extern void * SlotGetInt_15f720(R8 *q);
extern s32  DataTableStoreString_368ab0(Pool *o, void *v);
extern s32  VariantGetInt_15f780(R8 *q);
extern f32  VariantGetFloat_15f740(R8 *q);
extern const f32 D_0045B078;

s32 DataTableCmdEntrySetParams_3f4f10(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    f32  t6;
    f32  t7;
    f32  t10;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = AbilityDataGetKind0Rec_3f5db0(&p->slots[i]);
    if (e == 0) return 1;
    e->f00C = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f010 = VariantGetInt_15f780(src++);
    e->f014 = VariantGetInt_15f780(src++);
    e->f044 = VariantGetInt_15f780(src++);
    e->f046 = VariantGetInt_15f780(src++);
    t6 = D_0045B078;
    t7 = VariantGetFloat_15f740(src++);
    e->f03C = t7 * t6;
    e->f028 = VariantGetFloat_15f740(src++);
    t10 = VariantGetFloat_15f740(src);
    e->f03E = t10 * t6;
    return 1;
}
