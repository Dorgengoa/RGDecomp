#include "types.h"
/* normal 0x00506A70 -- tick the countdown down unless the pause flag at 0xA4
 * is set.  `sltu $2,$0,$2 / xori 1 / andi 0xFF` is `!(u32 > 0)` returned u8. */
typedef struct Obj { u8 pad00[0x8C]; u32 f8C; u8 pad90[0xA4 - 0x90]; u8 fA4; } Obj;
extern u8 normal_LeaderHudBannerCountdownTick_506a70(Obj *p);
u8 normal_LeaderHudBannerCountdownTick_506a70(Obj *p)
{
    u32 c = p->f8C;
    if (c != 0) {
        if (p->fA4 == 0) {
            p->f8C = c - 1;
        }
    }
    return !(p->f8C > 0);
}
