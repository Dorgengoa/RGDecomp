/* rgp:protos */
#define RGP_SELF_AiCollIgnoreTimerTick_2c10c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x261];
    s8 m261;
};

s32 AiCollIgnoreTimerTick_2c10c0(struct Obj0 *p0, s32 p1)
{
    s8 t0;
    s32 r0;
    s8 t1;

    if (p1 == 0) {
        return 0;
    }
    t0 = p0->m261;
    if (t0 > 0) {
        r0 = ((unsigned char)IsInBattle_288420());
        if ((r0 & 0xFF) == 0) {
            t1 = p0->m261;
            p0->m261 = (t1 + -1);
            CharaAddCollIgnoreMask_238920(p1, 2);
            return 1;
        }
        p0->m261 = 0;
    }
    return 0;
}
