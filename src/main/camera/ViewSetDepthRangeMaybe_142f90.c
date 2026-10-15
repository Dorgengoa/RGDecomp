#include "types.h"

extern void ViewSetProjection_143000(f32, f32, f32, f32, f32, f32);

void ViewSetDepthRangeMaybe_142f90(void *arg0, f32 x, f32 y) {
    void *p;
    u8 *q;

    p = *(void **)((u8 *)arg0 + 0xF20);
    if (p != 0) {
        q = (u8 *)p + 0x14;
        if (x < 0.0f) {
            x = *(f32 *)(q + 0xC);
        }
        if (y < 0.0f) {
            y = *(f32 *)(q + 0x10);
        }
        ViewSetProjection_143000(*(f32 *)q, *(f32 *)(q + 0xC), *(f32 *)(q + 0x10), *(f32 *)(q + 0x30), x, y);
    }
}
