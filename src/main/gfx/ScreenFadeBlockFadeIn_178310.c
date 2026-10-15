#include "types.h"

typedef struct T178310 {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    s32 f10;
    s32 f14;
    f32 f18;
    s32 f1C;
    u8  pad20[4];
    s32 f24;
} T178310;

void ScreenFadeBlockFadeIn_178310(T178310 *p, s32 n)
{
    f32 a;
    f32 b;
    f32 c;

    if (p->f10 >= 0) {
        if (p->f10 == 0 || n < 0) {
            p->f0C = 128.0f;
        }
        p->f10 = 1;
        p->f14 = 0;
        if (n <= 0) {
            p->f18 = 255.0f;
        } else {
            p->f18 = 128.0f / (f32)n;
        }
        p->f00 = 0.0f;
        p->f04 = 0.0f;
        p->f08 = 0.0f;
        p->f24 = 0;
        p->f1C = 0;
    } else {
        c = p->f08;
        b = p->f04;
        a = p->f00;
        if (p->f10 == 0 || n < 0) {
            p->f0C = 128.0f;
        }
        p->f10 = 1;
        p->f14 = 0;
        if (n <= 0) {
            p->f18 = 255.0f;
        } else {
            p->f18 = 128.0f / (f32)n;
        }
        p->f00 = a;
        p->f04 = b;
        p->f08 = c;
        p->f24 = 0;
        p->f1C = 0;
    }
}
