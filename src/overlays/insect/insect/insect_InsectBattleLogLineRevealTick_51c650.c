#include "types.h"
/* insect 0x0051C650 -- 32 bytes, 8 instructions.  A saturating decrement that
 * RETURNS the member: retail loads 0x56 three times (guard, decrement, return),
 * so the source reads the member at every use and keeps no named local. */

typedef struct Obj {
    u8  pad00[0x56];
    s16 m56;                        /* +0x56 */
} Obj;

s16 insect_InsectBattleLogLineRevealTick_51c650(Obj *o)
{
    if (o->m56 > 0) {
        o->m56 = o->m56 - 1;
    }
    return o->m56;
}
