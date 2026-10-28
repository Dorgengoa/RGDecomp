/* rgp:protos */
#define RGP_SELF_EvMapObjPartSetVelFromPrev_363ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef union Vec4 {
    u128 q;
    f32 f[4];
    s32 i[4];
} Vec4;

/*rgp*/

void EvMapObjPartSetVelFromPrev_363ef0(u8 *base)
{
    Vec4 v60, v50, v40;
    s32 i;
    u8 *p;

    for (i = 0; i < 3; i++) {
        p = base + i * 0x40;
        v60.q = *(u128 *)p;
        v50.f[0] = *(f32 *)(p + 0x20);
        v50.f[1] = *(f32 *)(p + 0x24);
        v50.f[2] = *(f32 *)(p + 0x28);
        v50.i[3] = 0x3F800000;
        VecSub_13be40(&v40, &v60, &v50);
        v40.f[1] = v40.f[1] - 2.5f;
        *(u128 *)(p + 0x10) = v40.q;
    }
}
