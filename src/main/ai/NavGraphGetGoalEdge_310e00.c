#include "types.h"

struct T310E00 { u8 pad000[0x114]; s32 f114; };

extern s32 NavGraphGetEdge_310c20(struct T310E00 *, s32);

s32 NavGraphGetGoalEdge_310e00(struct T310E00 *p)
{
    s32 v;

    v = p->f114;
    if (v < 0) {
        return 0;
    }
    return NavGraphGetEdge_310c20(p, v);
}
