/* rgp:protos */
#define RGP_SELF_NavGraphGetGoalEdge_310e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T310E00 { u8 pad000[0x114]; s32 f114; };

/*rgp*/

s32 NavGraphGetGoalEdge_310e00(struct T310E00 *p)
{
    s32 v;

    v = p->f114;
    if (v < 0) {
        return 0;
    }
    return ((s32)NavGraphGetEdge_310c20(p, v));
}
