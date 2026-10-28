/* rgp:protos */
#define RGP_SELF_ActCfgTableAddTimeMoveRefs_21fbc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* pair-array forwarding loop. `beqz` on the list falls through into the
   loop, so the loop IS the if body; the trailing `bnel` re-loads
   list->a into $6 in its delay slot. */

typedef struct { s32 a; s32 b; } Pair;

/*rgp*/

void ActCfgTableAddTimeMoveRefs_21fbc0(void *p, void *q, Pair *list, s32 n, f32 x, f32 y)
{
    s32 i;

    if (list != 0) {
        for (i = 0; i < n; i++, list++) {
            ActCfgTableAddTimeMove_21fc60(p, q, list->a, list->b, x, y);
        }
    }
}
