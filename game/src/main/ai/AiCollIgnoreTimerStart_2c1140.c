/* rgp:protos */
#define RGP_SELF_AiCollIgnoreTimerStart_2c1140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x261];
    u8 m261;
};

void AiCollIgnoreTimerStart_2c1140(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;

    if (p1 != 0) {
        r0 = ((unsigned char)IsInBattle_288420());
        if ((r0 & 0xFF) != 0) {
            return;
        }
        p0->m261 = p2;
        CharaAddCollIgnoreMask_238920(p1, 2);
        return;
    }
}
