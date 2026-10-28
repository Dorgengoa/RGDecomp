/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLogLineFadeStep_51c740 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051C740 -- 144 bytes, 36 instructions, no calls.
 * f51 walks toward the target f52 at velocity f53, clamping and zeroing
 * the velocity on arrival; gated on f56 >= 0. */

typedef struct Obj {
    u8  pad00[0x51];
    u8  f51;                        /* +0x51 */
    u8  f52;                        /* +0x52 */
    s8  f53;                        /* +0x53 */
    u8  pad54[0x56 - 0x54];
    s16 f56;                        /* +0x56 */
} Obj;

void insect_InsectBattleLogLineFadeStep_51c740(Obj *o)
{
    s32 t;

    if (o->f56 >= 0) {
        if (o->f53 > 0) {
            t = o->f51 + o->f53;
            if (t > 0xFF) {
                t = 0xFF;
            }
            if (t >= o->f52) {
                t = o->f52;
                o->f53 = 0;
            }
            o->f51 = t;
        }
        if (o->f53 < 0) {
            t = o->f51 + o->f53;
            if (t < 0) {
                t = 0;
            }
            if (t <= o->f52) {
                t = o->f52;
                o->f53 = 0;
            }
            o->f51 = t;
        }
    }
}
