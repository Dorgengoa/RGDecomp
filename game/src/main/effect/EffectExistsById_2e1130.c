/* rgp:protos */
#define RGP_SELF_EffectExistsById_2e1130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct B2e1130 {
    u8 pad000[0x8];
    s32 m08;
    u8 pad00C[0x14];
};

/*rgp*/

s32 EffectExistsById_2e1130(u8 *p0, s32 p1)
{
    struct B2e1130 b __attribute__((aligned(16)));

    EffectFindHandleById_2dd6c0(&b, p0 + 0x1674, p1);
    return (b.m08 < 0) ^ 1;
}
