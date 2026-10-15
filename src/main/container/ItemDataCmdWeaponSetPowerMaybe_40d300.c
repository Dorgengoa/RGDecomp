#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x6];
    u16 b006_0 : 10;
    u16 pb006_10 : 6;
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

s32 ItemDataCmdWeaponSetPowerMaybe_40d300(R8 *src)
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
    e->b006_0 = VariantGetInt_15f780(src);
    return 1;
}
