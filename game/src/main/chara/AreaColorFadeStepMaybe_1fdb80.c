/* rgp:protos */
#define RGP_SELF_AreaColorFadeStepMaybe_1fdb80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T1fdb80 {
    f32 a[4];
    f32 b[4];
    f32 c[4];
    s32 f30;
    s32 f34;
} T1fdb80;

void AreaColorFadeStepMaybe_1fdb80(T1fdb80 *t)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        t->a[i] = t->a[i] + t->c[i];
        if (t->c[i] > 0.0f) {
            if (!(t->a[i] < t->b[i])) {
                t->a[i] = t->b[i];
                t->c[i] = 0.0f;
            }
        } else {
            if (t->c[i] < 0.0f) {
                if (t->a[i] <= t->b[i]) {
                    t->a[i] = t->b[i];
                    t->c[i] = 0.0f;
                }
            }
        }
    }
    if (t->f30 != t->f34) {
        if (t->c[0] == 0.0f) {
            if (t->c[1] == 0.0f) {
                if (t->c[2] == 0.0f) {
                    if (t->c[3] == 0.0f) {
                        t->f30 = t->f34;
                    }
                }
            }
        }
    }
}
