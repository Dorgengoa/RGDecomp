/* rgp:protos */
#define RGP_SELF_AreaColorFadeSetMaybe_1fdc70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T1fdc70 {
    f32 p[4];
    f32 q[4];
    f32 d[4];
    s32 t0;
    s32 t1;
} T1fdc70;

void AreaColorFadeSetMaybe_1fdc70(T1fdc70 *a, s32 key, f32 *src, s32 n)
{
    f32 f;

    if (a->t0 < 0 || n <= 0) {
        a->t0 = key;
        a->t1 = key;
        a->p[0] = src[0];
        a->p[1] = src[1];
        a->p[2] = src[2];
        a->p[3] = src[3];
        a->q[0] = src[0];
        a->q[1] = src[1];
        a->q[2] = src[2];
        a->q[3] = src[3];
        a->d[0] = 0.0f;
        a->d[1] = 0.0f;
        a->d[2] = 0.0f;
        a->d[3] = 0.0f;
    } else {
        if (a->t1 == key) {
            return;
        }
        a->t1 = key;
        f = (f32)n;
        a->q[0] = src[0];
        a->q[1] = src[1];
        a->q[2] = src[2];
        a->q[3] = src[3];
        a->d[0] = (a->q[0] - a->p[0]) / f;
        a->d[1] = (a->q[1] - a->p[1]) / f;
        a->d[2] = (a->q[2] - a->p[2]) / f;
        a->d[3] = (a->q[3] - a->p[3]) / f;
    }
}
