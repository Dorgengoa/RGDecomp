/* rgp:protos */
#define RGP_SELF_ModelHasMotion_20a5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T20A5B0 { u8 pad000[0x1F0]; s32 f1F0; s32 f1F4; s32 f1F8; };

/*rgp*/

s32 ModelHasMotion_20a5b0(struct T20A5B0 *p, void *a)
{
    s32 loc[3];
    s32 x;
    s32 y;
    s32 r;

    if (p == 0 || a == 0) {
        r = 0;
    } else {
        loc[0] = p->f1F0;
        loc[1] = p->f1F4;
        loc[2] = p->f1F8;
        r = ((s32)MotionListFindByName_1721d0(loc, a, &x, &y));
    }
    return r != 0;
}
