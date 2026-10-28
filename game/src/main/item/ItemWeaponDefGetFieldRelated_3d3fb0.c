/* rgp:protos */
#define RGP_SELF_ItemWeaponDefGetFieldRelated_3d3fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S3D3FB0 { u8 pad000[0x4]; __extension__ unsigned short f04_a : 7; unsigned short f04_b : 9; } __attribute__((aligned(2)));
struct T3D3FB0 { u8 pad000[0x10]; void *f10; };

/*rgp*/

s32 ItemWeaponDefGetFieldRelated_3d3fb0(struct T3D3FB0 *p)
{
    struct S3D3FB0 *q;

    q = ((struct S3D3FB0 *)ItemDefGetWeaponData_40e110(p->f10));
    if (q != 0) {
        return q->f04_b;
    }
    return 0;
}
