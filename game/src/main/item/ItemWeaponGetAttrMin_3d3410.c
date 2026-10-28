/* rgp:protos */
#define RGP_SELF_ItemWeaponGetAttrMin_3d3410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_003d3410 {
    u8 pad0[0x10];
    void *f10;
} S_003d3410;

/*rgp*/

u32 ItemWeaponGetAttrMin_3d3410(S_003d3410 *self, s32 i)
{
    u8 *p;
    if (i < 0) goto zero;
    if (i < 5) goto ok;
zero:
    return (u8)(0);
ok:
    p = ((u8 *)ItemDefGetWeaponData_40e110(self->f10));
    if (p != 0) {
        return (u8)(p[i * 2 + 0x18]);
    }
    return (u8)(0);
}
