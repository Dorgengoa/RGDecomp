/* rgp:protos */
#define RGP_SELF_SwordTrailSetEndRef_2159b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void SwordTrailSetEndRef_2159b0(u8 *base, s32 i, void *a, void *b, void *c)
{
    if (i < 0 || i >= 2) return;
    TargetRefSetModelFrame_2e6560(base + i * 48 + 0x30, a, b, c, 0.0f);
}
