#include "types.h"

typedef struct { u8 pad[0x24]; f32 f24; s32 f28_pad; f32 f28; f32 f2C; s32 f30; } T_001ce760_bad;
typedef struct {
    u8 pad[0x24];
    f32 f24;
    f32 f28;
    f32 f2C;
    s32 f30;
} T_001ce760;

void DoorGlareParamsStep_1ce760(T_001ce760 *p)
{
    f32 cur;
    f32 tgt;
    f32 step;

    if (p->f30 == 0) return;
    cur = p->f2C;
    tgt = p->f24;
    if (cur == tgt) {
        p->f30 = 0;
        return;
    }
    step = p->f28;
    p->f2C = cur + step;
    if (p->f28 < 0.0f) {
        if (p->f2C < p->f24) {
            p->f2C = p->f24;
        }
    } else {
        if (p->f2C > p->f24) {
            p->f2C = p->f24;
        }
    }
}
