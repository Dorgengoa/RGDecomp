/* rgp:protos */
#define RGP_SELF_GuardEffectStart_2d53e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* the three tail calls read 0x330, pass it, and store back +1: a POST
   INCREMENT through the member, not a local counter. */

/*rgp*/
/*rgp*/
/*rgp*/

void GuardEffectStart_2d53e0(void *p, void *a, void *b)
{
    u8 *q;
    s32 i;

    q = (u8 *)p;
    sceVu0CopyVector(p, a);
    *(f32 *)(q + 0x0C) = 1.0f;
    sceVu0CopyVector(q + 0x10, b);
    sceVu0Normalize(q + 0x10, q + 0x10);
    *(s32 *)(q + 0x320) = 0x10;
    *(f32 *)(q + 0x328) = 30.0f;
    *(s32 *)(q + 0x334) = 1;
    *(s32 *)(q + 0x330) = 0;
    for (i = 0; i < 0x10; i++) {
        *(s32 *)(q + i * 48 + 0x40) = 0;
    }
    GuardEffectInitStreak_2d54c0(p, (*(s32 *)(q + 0x330))++);
    GuardEffectInitStreak_2d54c0(p, (*(s32 *)(q + 0x330))++);
    GuardEffectInitStreak_2d54c0(p, (*(s32 *)(q + 0x330))++);
}
