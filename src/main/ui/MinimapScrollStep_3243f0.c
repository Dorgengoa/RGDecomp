#include "types.h"

typedef struct { u8 pad[0x30]; f32 a[4]; f32 b[4]; f32 c[4]; f32 d[4]; } S3243f0;

s32 MinimapScrollStep_3243f0(S3243f0 *s) {
    s32 i;
    f32 v;
    f32 lim;
    f32 *pd;
    f32 *pb;

    i = 0;
    do {
        pd = &s->d[i];
        v = *pd;
        if (!(v <= 0.0f)) {
            s->b[i] += v;
            lim = s->a[i];
            lim = s->c[i] - lim;
            pb = &s->b[i];
            if (!(s->b[i] < lim)) {
                *pb = lim;
                *pd = 0.0f;
            }
        } else if (v < 0.0f) {
            s->b[i] += v;
            lim = s->a[i];
            lim = s->c[i] - lim;
            pb = &s->b[i];
            if (s->b[i] <= lim) {
                *pb = lim;
                *pd = 0.0f;
            }
        }
        i++;
    } while (i < 3);
    return 1;
}
