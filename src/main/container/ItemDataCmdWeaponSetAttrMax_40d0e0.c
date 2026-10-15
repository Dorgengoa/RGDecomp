#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Rec0 {
    u8  a000;
    u8  pad001[0x1];
} Rec0;

typedef struct Ent {
    u8  pad000[0x19];
    Rec0 f019[5];
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

s32 ItemDataCmdWeaponSetAttrMax_40d0e0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = ItemDefGetWeaponData_40e110(&p->slots[i]);
    if (e == 0) return 1;
    for (k0 = 0; k0 < 0x5; k0++) e->f019[k0].a000 = VariantGetInt_15f780(src++);
    return 1;
}
