/* rgp:protos */
#define RGP_SELF_FieldHudRowsSettled_203d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00527020[];
/*rgp*/

s32 FieldHudRowsSettled_203d30(void)
{
    return func_4F53D0(D_00527020) != 0;
}
