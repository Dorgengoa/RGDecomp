/* rgp:protos */
#define RGP_SELF_ItemDataCmdSpecialWeaponSetParams_40cbc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x2C];
    u8  f02C;
    u8  f02D;
    u8  f02E;
    u8  pad02F[0x1];
    s16 f030;
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
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B078;

s32 ItemDataCmdSpecialWeaponSetParams_40cbc0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    f32  t3;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = ((Ent *)ItemDefGetSpecialWeaponData_40e0e0(&p->slots[i]));
    if (e == 0) return 1;
    e->f02C = VariantGetInt_15f780(src++);
    e->f02D = VariantGetInt_15f780(src++);
    e->f02E = VariantGetInt_15f780(src++);
    t3 = VariantGetFloat_15f740(src);
    e->f030 = t3 * D_0045B078;
    return 1;
}
