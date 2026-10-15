#include "types.h"

/* pair-array forwarding loop. `beqz` on the list falls through into the
   loop, so the loop IS the if body; the trailing `bnel` re-loads
   list->a into $6 in its delay slot. */

typedef struct { s32 a; s32 b; } Pair;

extern void ActCfgTableRunTimeEvnts_221f40(void *p, void *q, s32 a, s32 b, f32 x, f32 y);

void ActCfgTableRunTimeEvntRefs_221ea0(void *p, void *q, Pair *list, s32 n, f32 x, f32 y)
{
    s32 i;

    if (list != 0) {
        for (i = 0; i < n; i++, list++) {
            ActCfgTableRunTimeEvnts_221f40(p, q, list->a, list->b, x, y);
        }
    }
}
