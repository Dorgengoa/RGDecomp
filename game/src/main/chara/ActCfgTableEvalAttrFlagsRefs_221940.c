/* rgp:protos */
#define RGP_SELF_ActCfgTableEvalAttrFlagsRefs_221940 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* `bnez` PAST the `return 0` => the early return is the if body. */

typedef struct { s32 a; s32 b; } Pair;

/*rgp*/

long long ActCfgTableEvalAttrFlagsRefs_221940(void *p, Pair *list, s32 n, f32 x)
{
    long long r;
    s32 i;

    if (list == 0) {
        return 0;
    }
    r = 0;
    for (i = 0; i < n; i++, list++) {
        r |= ActCfgTableEvalAttrFlags_2219e0(p, list->a, list->b, x);
    }
    return r;
}
