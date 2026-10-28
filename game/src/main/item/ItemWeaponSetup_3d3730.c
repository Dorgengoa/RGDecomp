/* rgp:protos */
#define RGP_SELF_ItemWeaponSetup_3d3730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent_FUN_003d3730 {
    u8 pad000[0x1];
    u8 f01;
} Ent_FUN_003d3730;

typedef struct T_FUN_003d3730 {
    u8 pad000[0x18];
    Ent_FUN_003d3730 e[1];
} T_FUN_003d3730;

typedef struct Obj_FUN_003d3730 {
    u8 pad000[0x10];
    s32 f10;
    u8 pad014[0x2];
    u8 f16;
    u8 f17[1];
} Obj_FUN_003d3730;

/*rgp*/
/*rgp*/

s32 ItemWeaponSetup_3d3730(Obj_FUN_003d3730 *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    T_FUN_003d3730 *t;
    s32 i;

    ItemSetup_3d4ff0(o, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    o->f16 = 0;
    t = ((T_FUN_003d3730 *)ItemDefGetWeaponData_40e110(o->f10));
    if (t == 0) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        o->f17[i] = *(u8 *)((u8 *)t + i * 2 + 0x18);
    }
    return 1;
}
