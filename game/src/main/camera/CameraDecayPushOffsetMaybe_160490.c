/* rgp:protos */
#define RGP_SELF_CameraDecayPushOffsetMaybe_160490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Retail falls through into the three-element decay loop, so THAT is the `if`
   body; the quadword clear is the else arm (its `sq` rides the bc1tl delay
   slot). */

typedef rg_u128 u128;

extern f32 D_0047D5D0;
/*rgp*/

void CameraDecayPushOffsetMaybe_160490(u8 *p)
{
    f32 v;
    s32 i;

    v = VecLength_13d4a0(p + 0x200);
    if (v > D_0047D5D0) {
        for (i = 0; i < 3; i++) {
            *(f32 *)(p + 0x200 + i * 4) =
                *(f32 *)(p + 0x200 + i * 4) - *(f32 *)(p + 0x200 + i * 4) / 8.0f;
        }
    } else {
        *(u128 *)(p + 0x200) = 0;
    }
}
