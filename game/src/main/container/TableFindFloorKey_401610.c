/* rgp:protos */
#define RGP_SELF_TableFindFloorKey_401610 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { __extension__ signed short v : 10; } __attribute__((aligned(2))) B401610;
/*rgp*/
/*rgp*/

B401610 *TableFindFloorKey_401610(s32 arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    s64 it;
    B401610 *best;
    B401610 *p;
    s32 x;

    best = NULL;
    x = arg0;
    if (x != 0) x += 4;
    IterInit_370170(&it, x, (int)rgp_a2, (int)rgp_a3);
    while ((p = ((B401610 *)IterNext_370040(&it))) != NULL) {
        if (p->v > arg1) continue;
        if (best == NULL || best->v < p->v) {
            best = p;
        }
    }
    return best;
}
