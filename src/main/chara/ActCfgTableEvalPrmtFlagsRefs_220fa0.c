#include "types.h"

/* `bnez` PAST the `return 0` => the early return is the if body. */

typedef struct { s32 a; s32 b; } Pair;

extern s32 ActCfgTableEvalPrmtFlags_2210e0(void *p, s32 a, s32 b, f32 x);

s32 ActCfgTableEvalPrmtFlagsRefs_220fa0(void *p, Pair *list, s32 n, f32 x)
{
    s32 r;
    s32 i;

    if (list == 0) {
        return 0;
    }
    r = 0;
    for (i = 0; i < n; i++, list++) {
        r |= ActCfgTableEvalPrmtFlags_2210e0(p, list->a, list->b, x);
    }
    return r;
}
