/* rgp:protos */
#define RGP_SELF_InRangeWrap_1922b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 InRangeWrap_1922b0(f32 fparg0, f32 fparg1, f32 fparg2)
{
    s32 var_2;
    s32 var_2_2;

    if (!(fparg2 <= fparg1)) {
        if (fparg0 < fparg1) {
            return 0;
        }
        var_2_2 = 1;
        if (fparg0 < fparg2) {
            var_2_2 = 0;
        }
        var_2 = var_2_2 ^ 1;
        return var_2 & 0xFF;
    }
    if (!(fparg1 <= fparg2)) {
        if (!(fparg0 < fparg1)) {
            return 1;
        }
        var_2 = 1;
        if (!(fparg0 < fparg2)) {
            var_2 = 0;
        }
        return var_2 & 0xFF;
    }
    return 1;
}
