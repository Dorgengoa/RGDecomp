/* rgp:protos */
#define RGP_SELF_MotionEventSetStartRatio_1b1cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D24C;
extern f32 D_0047D3E8;

void MotionEventSetStartRatio_1b1cc0(void *arg0, f32 fparg0) {
    f32 t;
    f32 result;
    f32 frac;
    f32 a;
    f32 b;
    void *p;

    if (fparg0 <= 0.0f) {
        t = 0.0f;
    } else {
        if (!(fparg0 < 1.0f)) {
            t = 1.0f;
        } else {
            t = fparg0;
        }
    }
    p = *(void **)((u8 *)arg0 + 0x14);
    if (p == NULL) {
        result = 0.0f;
    } else {
        a = *(f32 *)((u8 *)p + 0x24);
        b = *(f32 *)((u8 *)p + 0x28);
        result = a + t * (b - a);
        frac = result - (f32)(s32)result;
        frac = frac < 0.0f ? -frac : frac;
        if (!(frac <= D_0047D3E8)) {
            result = (f32)(s32)(D_0047D24C + result);
        }
    }
    *(f32 *)((u8 *)arg0 + 0x8) = result;
    *(f32 *)((u8 *)arg0 + 0x1C) = t;
}
