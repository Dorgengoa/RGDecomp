/* rgp:protos */
#define RGP_SELF_SplineStep_257190 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct Key {
    s32 start;
    s32 len;
    f32 a[3];
    f32 b[3];
    f32 c[3];
    f32 d[3];
} Key;

typedef struct Anim {
    Key k[16];
    s32 count;
    s32 cur;
    f32 time;
    f32 out[3];
} Anim;

s32 SplineStep_257190(Anim *an)
{
    s32 i;
    s32 cur;
    f32 t;
    f32 t2;
    f32 t3;

    if (an->count < 2) {
        return 1;
    }
    an->time = an->time + 1.0f;
    if (!(an->time < (f32)(an->k[an->cur].start + an->k[an->cur].len))) {
        if (++an->cur >= an->count) {
            for (i = 0; i < 3; i++) {
                an->out[i] = an->k[an->count - 1].d[i];
            }
            an->cur = an->count - 1;
            an->time = 100.0f + (f32)(an->k[an->cur].start + an->k[an->cur].len);
            return 1;
        }
    }
    t = (an->time - (f32)an->k[an->cur].start) / (f32)an->k[an->cur].len;
    t2 = t * t;
    t3 = t2 * t;
    for (i = 0; i < 3; i++) {
        an->out[i] = an->k[an->cur].d[i] + (an->k[an->cur].a[i] * t3 + an->k[an->cur].b[i] * t2 + an->k[an->cur].c[i] * t);
    }
    return 0;
}
