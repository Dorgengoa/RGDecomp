/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLogWaitTick_51c140 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051C140 -- 64 bytes, 16 instructions.
 * f20 is RE-LOADED after each decrement, so it is touched through the
 * pointer and never cached in a named local. */

typedef struct Timer {
    u8  pad00[0x20];
    s16 f20;                        /* +0x20 */
    u8  pad22[0x25 - 0x22];
    u8  f25;                        /* +0x25 */
} Timer;

s16 insect_InsectBattleLogWaitTick_51c140(Timer *t)
{
    if (t->f20 > 0) {
        t->f20 = t->f20 - 1;
        if (t->f25 != 0) {
            if (t->f20 > 0) {
                t->f20 = t->f20 - 1;
            }
        }
    }
    return t->f20;
}
