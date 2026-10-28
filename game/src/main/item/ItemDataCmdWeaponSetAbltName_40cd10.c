/* rgp:protos */
#define RGP_SELF_ItemDataCmdWeaponSetAbltName_40cd10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x7];
    u8  pb007_0 : 2;
    u8  b007_2 : 1;
    u8  b007_3 : 1;
    u8  pb007_4 : 4;
    u8  pad008[0x1C];
    s32 f024;
    s16 f028;
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
/*rgp*/

s32 ItemDataCmdWeaponSetAbltName_40cd10(R8 *src)
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
    e->f024 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f028 = VariantGetInt_15f780(src++);
    e->b007_2 = VariantGetInt_15f780(src++);
    e->b007_3 = VariantGetInt_15f780(src);
    return 1;
}
