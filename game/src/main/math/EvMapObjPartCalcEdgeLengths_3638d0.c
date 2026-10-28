/* rgp:protos */
#define RGP_SELF_EvMapObjPartCalcEdgeLengths_3638d0 1
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
/*rgp*/

void EvMapObjPartCalcEdgeLengths_3638d0(u8 *o)
{
    Vec4 v __attribute__((aligned(16)));

    VecSub_13be40(&v, o + 0xD0, o + 0xC0);
    *(f32 *)(o + 0x120) = VecLength_13d4a0(&v);
    VecSub_13be40(&v, o + 0xE0, o + 0xD0);
    *(f32 *)(o + 0x124) = VecLength_13d4a0(&v);
    VecSub_13be40(&v, o + 0xC0, o + 0xE0);
    *(f32 *)(o + 0x128) = VecLength_13d4a0(&v);
}
