#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3;

typedef struct {
    u8 pad0[0x36B4];
    s32 unk36B4;
} G;

extern f32 sqrtf(f32);
void LightSlotSet_156af0(s32, s32, s32, V3 *, f32);
extern G *D_004810A4;

void LightStateSetPointLight_15ca80(s32 arg0, s32 arg1, V3 *arg2, f32 k) {
    f32 x;
    f32 y;
    f32 m;
    s32 h;

    h = D_004810A4->unk36B4;
    if (h == 0) {
        return;
    }
    y = arg2->y;
    x = arg2->x;
    if (x > y) {
        m = (x > arg2->z) ? x : arg2->z;
    } else {
        m = (y > arg2->z) ? y : arg2->z;
    }
    { f32 s = k * sqrtf(m); LightSlotSet_156af0(h, arg0, arg1, arg2, 0.5f * (s + k)); }
}
