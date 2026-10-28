/* rgp:protos */
#define RGP_SELF_MapSceneCfgLight_192dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 *D_00481304;

s32 MapSceneCfgLight_192dd0(s64 *arg0, s32 arg1)
{
    u128 sp40;
    s32 temp_2;

    if (D_00481304 == NULL) {
        return 0;
    }
    temp_2 = VariantGetInt_15f780(arg0++);
    if (temp_2 < 0 || temp_2 > 3) {
        return 0;
    }
    if (arg1 < 4) {
        return 0;
    }
    VariantReadVec3_15f6c0(&sp40, arg0);
    VecNormalize_13bd90(&sp40, &sp40);
    temp_2 *= 0x10;
    *(u128 *)(D_00481304 + temp_2 + 0x30) = sp40;
    if (arg1 >= 7) {
        VariantReadVec3_15f6c0(&sp40, arg0 + 3);
        ((u32 *)&sp40)[3] = 0;
        *(u128 *)(D_00481304 + temp_2 + 0x70) = sp40;
    }
    return 1;
}
