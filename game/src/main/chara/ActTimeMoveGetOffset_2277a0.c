/* rgp:protos */
#define RGP_SELF_ActTimeMoveGetOffset_2277a0 1
#define RGP_SELF_check 1
#include "port/game_protos.h"
#line 1
#include "types.h"

static inline u8 check(f32 f3, f32 f2, f32 a, f32 b)
{
    if (0.0f <= f3 && a + b < f3) {
        return 0;
    }
    if (!(1.0f < f2) && !(a <= f2)) {
        return 0;
    }
    return f3 <= f2;
}

void ActTimeMoveGetOffset_2277a0(void *arg0, void *arg1, f32 fparg0, f32 fparg1)
{
    f32 t;
    f32 f3;
    f32 f2;
    f32 lo;
    f32 hi;

    f2 = *(f32 *)((u8 *)arg0 + 0x4);
    f3 = *(f32 *)((u8 *)arg0 + 0x0);
    if (!(f3 < f2) || !check(f3, f2, fparg0, fparg1)) {
        *(f32 *)((u8 *)arg1 + 0x0) = 0.0f;
        *(f32 *)((u8 *)arg1 + 0x4) = 0.0f;
        *(f32 *)((u8 *)arg1 + 0x8) = 0.0f;
        *(s32 *)((u8 *)arg1 + 0xC) = 0;
    } else {
        hi = fparg0 + fparg1;
        lo = fparg0;
        if (lo < f3) {
            lo = f3;
        }
        if (!(hi <= f2)) {
            hi = f2;
        }
        if (lo < 0.0f) {
            lo = 0.0f;
        }
        if (!(hi <= 1.0f)) {
            hi = 1.0f;
        }
        t = (hi - lo) / (f2 - f3);
        *(f32 *)((u8 *)arg1 + 0x0) = t * *(f32 *)((u8 *)arg0 + 0x8);
        *(f32 *)((u8 *)arg1 + 0x4) = t * *(f32 *)((u8 *)arg0 + 0xC);
        *(f32 *)((u8 *)arg1 + 0x8) = t * *(f32 *)((u8 *)arg0 + 0x10);
        *(s32 *)((u8 *)arg1 + 0xC) = 0;
    }
}
