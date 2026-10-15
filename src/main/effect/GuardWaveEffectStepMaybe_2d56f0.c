#include "types.h"
#pragma optimization_level 3

typedef struct Fade {
    s32 active;      /* +0x00 */
    u8 pad04[0x1C];
    f32 a[2];        /* +0x20 */
    f32 b[2];        /* +0x28 */
    s16 wait[2];     /* +0x30 */
    s16 state[2];    /* +0x34 */
} Fade;

extern void GuardWaveEffectReset_2d5660(Fade *p);

void GuardWaveEffectStepMaybe_2d56f0(Fade *p)
{
    s32 i;
    s16 st;
    if (p->active != 0) {
        for (i = 0; i < 2; i++) {
            if ((st = p->state[i]) != 0) {
                if (p->wait[i] > 0) {
                    p->wait[i]--;
                } else {
                    if (st == 1) {
                        if (p->b[i] < 128.0f) {
                            p->b[i] += 0.23333333f;
                        }
                        p->a[i] += 0.23333333f;
                        if (p->a[i] > 1.0f) {
                            p->state[i] = 2;
                        }
                    }
                    if (p->state[i] == 2) {
                        p->a[i] += 0.030000001f;
                        p->b[i] -= 0.1f;
                        if (p->b[i] < 0.0f) {
                            p->state[i] = 0;
                        }
                    }
                }
            }
        }
        if (p->active != 0 && p->state[0] == 0 && p->state[1] == 0) {
            GuardWaveEffectReset_2d5660(p);
        }
    }
}
