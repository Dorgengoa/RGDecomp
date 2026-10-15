#include "types.h"

typedef struct { f32 x; f32 y; f32 z; } V20a0c0;
typedef struct { s32 a; s32 b; V20a0c0 v; } E20a0c0;
typedef struct { E20a0c0 *p; s16 n; } T20a0c0;

void GameReqListPopFront_20a0c0(T20a0c0 *arg0)
{
    s32 i;
    E20a0c0 *d;
    E20a0c0 *s;

    if (arg0->p == 0 || arg0->n <= 0) return;
    for (i = 1; i < arg0->n; i++) {
        s = &arg0->p[i];
        d = &arg0->p[i - 1];
        d->a = s->a;
        d->b = s->b;
        d->v = s->v;
    }
    arg0->n--;
}
