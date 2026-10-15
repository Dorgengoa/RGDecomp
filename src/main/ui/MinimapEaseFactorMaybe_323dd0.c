#include "types.h"

extern f32 Cosf_128d30(f32 arg0);
extern f32 D_0047D804;
extern f32 D_00482B98;

f32 MinimapEaseFactorMaybe_323dd0(void *arg0) {
    f32 bound = D_00482B98;
    f32 v = *(f32 *)((u8 *)arg0 + 0x16C);

    if (v >= bound) {
        return 1.0f;
    }
    {
        f32 ratio = D_0047D804 / bound;
        f32 vv = v;
        return (1.0f + Cosf_128d30(ratio * vv)) / 2.0f;
    }
}
