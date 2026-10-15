#include "types.h"
typedef struct {
    u8 pad0[0xCC];
    f32 ang;
    f32 rad;
    f32 s;
    f32 c;
} O;

f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
extern f32 GetQuadrantAngle_324120(O *);
extern const f32 D_0047D1FC __attribute__((section(".sdata")));

void MinimapSetAngle_324160(O *o, f32 a) {
    f32 t;

    a = (180.0f * a) / D_0047D1FC;
    if (a > 360.0f) {
        while (a > 360.0f) {
            a -= 360.0f;
        }
    }
    if (a < 0.0f) {
        while (a < 0.0f) {
            a += 360.0f;
        }
    }
    if (o->ang == a) {
        return;
    }
    o->ang = a;
    t = (*(f32 *)&D_0047D1FC * GetQuadrantAngle_324120(o)) / 180.0f;
    o->rad = t;
    o->s = -Sinf_128fd0(t);
    o->c = Cosf_128d30(o->rad);
}
