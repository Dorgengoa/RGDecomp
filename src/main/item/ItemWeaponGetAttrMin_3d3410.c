#include "types.h"

typedef struct S_003d3410 {
    u8 pad0[0x10];
    void *f10;
} S_003d3410;

extern u8 *ItemDefGetWeaponData_40e110(void *);

u8 ItemWeaponGetAttrMin_3d3410(S_003d3410 *self, s32 i)
{
    u8 *p;
    if (i < 0) goto zero;
    if (i < 5) goto ok;
zero:
    return 0;
ok:
    p = ItemDefGetWeaponData_40e110(self->f10);
    if (p != 0) {
        return p[i * 2 + 0x18];
    }
    return 0;
}
