#include "types.h"

typedef struct { u8 pad[0x24]; s16 f24; s16 f26; f32 f28; f32 f2C; } T_0039dab0;

void WarpMenuFadeStep_39dab0(T_0039dab0 *p)
{
    if (p->f24 != 4) return;
    p->f28 = p->f28 + p->f2C;
    if (p->f28 < 0.0f) {
        p->f28 = 0.0f;
        if (p->f2C < 0.0f) {
            p->f2C = 0.0f;
        }
    }
    if (p->f28 > 1.0f) {
        p->f28 = 1.0f;
        if (p->f2C > 1.0f) {
            p->f2C = 0.0f;
        }
    }
}
