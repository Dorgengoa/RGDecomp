/* rgp:protos */
#define RGP_SELF_ItemDataCmdWeaponSetField4Maybe_40d3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x4];
    __extension__ unsigned short b004_0 : 7;
    unsigned short b004_7 : 9;
} __attribute__((aligned(2))) Ent;

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

s32 ItemDataCmdWeaponSetField4Maybe_40d3b0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = ((Ent *)ItemDefGetWeaponData_40e110(&p->slots[i]));
    if (e == 0) return 1;
    e->b004_0 = VariantGetInt_15f780(src++);
    e->b004_7 = (s32)(0.5f + VariantGetFloat_15f740(src));
    return 1;
}
