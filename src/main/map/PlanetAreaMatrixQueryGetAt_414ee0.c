#include "types.h"

typedef struct S414ee0 {
    u8 pad00[0x4];
    struct S414ee0 *m04;
    s16 m08;
} S414ee0;

extern s32 PlanetAreaMatrixFindNthInGroup_414f90(void *a, s32 b, void *c);

s32 PlanetAreaMatrixQueryGetAt_414ee0(S414ee0 *p, void *b)
{
    S414ee0 *t;

    t = p;
    p = p->m04;
    if (p == 0) {
        goto fail;
    }
    return PlanetAreaMatrixFindNthInGroup_414f90(p, t->m08, b);
fail:
    return 0;
}
