#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x4];
    u16 b004_0 : 7;
    u16 b004_7 : 9;
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
extern Ent *ItemDefGetWeaponData_40e110(Hdr *h);
extern s32  VariantGetInt_15f780(R8 *q);
extern f32  VariantGetFloat_15f740(R8 *q);

s32 ItemDataCmdWeaponSetField4Maybe_40d3b0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = ItemDefGetWeaponData_40e110(&p->slots[i]);
    if (e == 0) return 1;
    e->b004_0 = VariantGetInt_15f780(src++);
    e->b004_7 = (s32)(0.5f + VariantGetFloat_15f740(src));
    return 1;
}
