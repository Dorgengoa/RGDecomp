/* rgp:protos */
#define RGP_SELF_normal_LeaderHudSetField78Related_506960 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506960 -- three optional float stores, each skipped when the
 * argument equals -1.0f, then one unconditional byte store that the scheduler
 * duplicates into the last `bc1tl` delay slot. */
void normal_LeaderHudSetField78Related_506960(void *p, s32 f, f32 x, f32 y, f32 z)
{
    if (x != -1.0f) {
        *(f32 *)((u8 *)p + 0x7C) = x;
    }
    if (y != -1.0f) {
        *(f32 *)((u8 *)p + 0x78) = y;
    }
    if (z != -1.0f) {
        *(f32 *)((u8 *)p + 0x80) = z;
    }
    *(s8 *)((u8 *)p + 0x84) = f;
}
