#include "types.h"

struct S3D3FB0 { u8 pad000[0x4]; u16 f04_a : 7; u16 f04_b : 9; };
struct T3D3FB0 { u8 pad000[0x10]; void *f10; };

extern struct S3D3FB0 *ItemDefGetWeaponData_40e110(void *a);

s32 ItemWeaponDefGetFieldRelated_3d3fb0(struct T3D3FB0 *p)
{
    struct S3D3FB0 *q;

    q = ItemDefGetWeaponData_40e110(p->f10);
    if (q != 0) {
        return q->f04_b;
    }
    return 0;
}
