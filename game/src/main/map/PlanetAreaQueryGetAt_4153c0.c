/* rgp:protos */
#define RGP_SELF_PlanetAreaQueryGetAt_4153c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S4153c0 {
    u8 pad00[0x4];
    struct S4153c0 *m04;
    s16 m08;
} S4153c0;

/*rgp*/

s32 PlanetAreaQueryGetAt_4153c0(S4153c0 *p, void *b)
{
    S4153c0 *t;

    t = p;
    p = p->m04;
    if (p == 0) {
        goto fail;
    }
    return ((s32)PlanetAreaFindNthInGroup_415480(p, t->m08, b));
fail:
    return 0;
}
