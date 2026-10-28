/* rgp:protos */
#define RGP_SELF_PadGetAnalogLYNorm_183a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* `temp_2 > -0x32` and `temp_2 >= -0x31` are the same `slti $x,$v1,-49`, but
   the `>` form lands it in `$at` and the `>=` form in `$v0` -- and the choice
   also decides whether the subtracted value keeps `$v0` or is pushed to `$v1`,
   so all 7 residue words go together.
   [[levers.d/mwcc-compare-operator-picks-register]]. `<= 0x31` for the upper
   bound is inert (same object); `<= ` on the lower bound, a reversed
   `-0x31 <= temp_2` and `!(temp_2 < -0x31)` are all the 7-bad base. */
#pragma divbyzerocheck on
f32 PadGetAnalogLYNorm_183a50(void *arg0) {
    s32 temp_2;
    s32 var_2;

    temp_2 = *(s32 *)((u8 *)arg0 + 8) - 0x80;
    if ((temp_2 < 0x32) && (temp_2 > -0x32)) {
        var_2 = 0;
    } else if (temp_2 > 0) {
        var_2 = ((temp_2 - 0x31) << 7) / 78;
    } else {
        var_2 = ((temp_2 + 0x32) << 7) / 78;
    }
    return (f32) var_2 / 128.0f;
}
