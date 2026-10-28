/* rgp:protos */
#define RGP_SELF_insect_InsectModelMemNop_5128f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma schedule off
/* insect 0x005128F0 -- 12 bytes, 3 instructions.
 *
 * MEASURED, and it needs TWO levers that only pay TOGETHER:
 *   - the member is `volatile`, so the read survives dead-code elimination
 *     (a plain dead local is deleted outright -- 2 words, `jr`/`nop`);
 *   - `#pragma schedule off`, so the surviving load is NOT sunk into the
 *     `jr` delay slot (with the default schedule it is, and the unit is again
 *     2 words).
 * With both, the load lands in $3 rather than $2 because nothing claims the
 * return register.  Making it a real `return o->m00;` under `schedule off` is
 * the right LENGTH but puts the load in $2 -- one bad word.
 */

typedef struct Obj {
    volatile s32 m00;               /* +0x00 */
} Obj;

void insect_InsectModelMemNop_5128f0(Obj *o)
{
    o->m00;
}
