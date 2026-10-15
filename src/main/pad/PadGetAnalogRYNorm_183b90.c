#include "types.h"

/* Twin of PadGetAnalogLYNorm_183a50 (same body, field +0x10 instead of +8) and it takes the
   SAME two edits: `temp_2 > -0x32` for the lower bound
   ([[levers.d/mwcc-compare-operator-picks-register]]) and the `> 0` arm
   FIRST. The `<= 0` spelling with the arms swapped is semantically identical
   and 3 bad -- retail's `blezl` with `addiu $v1,$v0,50` annulled comes only
   from writing the positive arm first. */
#pragma divbyzerocheck on
f32 PadGetAnalogRYNorm_183b90(void *arg0)
{
    s32 temp_2;
    s32 var_2;

    temp_2 = *(s32 *)((u8 *)arg0 + 0x10) - 0x80;
    if ((temp_2 < 0x32) && (temp_2 > -0x32)) {
        var_2 = 0;
    } else if (temp_2 > 0) {
        var_2 = ((temp_2 - 0x31) << 7) / 78;
    } else {
        var_2 = ((temp_2 + 0x32) << 7) / 78;
    }
    return (f32) var_2 / 128.0f;
}
