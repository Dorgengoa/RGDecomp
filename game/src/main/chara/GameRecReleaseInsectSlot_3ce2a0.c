/* rgp:protos */
#define RGP_SELF_GameRecReleaseInsectSlot_3ce2a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Q { u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1;
                   u8 b4 : 1; u8 b5 : 1; u8 b6 : 1; u8 b7 : 1; } Q;

/*rgp*/

s32 GameRecReleaseInsectSlot_3ce2a0(void *rgp_a0, int rgp_a1)
{
    Q *q = ((Q *)GameRecGetInsectSlot_3ce350((void *)rgp_a0, (int)rgp_a1));
    if (q == 0) return 0;
    q->b0 = 0;
    q->b1 = 0;
    return 1;
}
