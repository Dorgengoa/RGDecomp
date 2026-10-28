/* rgp:protos */
#define RGP_SELF_PlanetAreaMatrixQueryGetAt_414ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S414ee0 {
    u8 pad00[0x4];
    struct S414ee0 *m04;
    s16 m08;
} S414ee0;

/*rgp*/

s32 PlanetAreaMatrixQueryGetAt_414ee0(S414ee0 *p, void *b)
{
    S414ee0 *t;

    t = p;
    p = p->m04;
    if (p == 0) {
        goto fail;
    }
    return ((s32)PlanetAreaMatrixFindNthInGroup_414f90(p, t->m08, b));
fail:
    return 0;
}
