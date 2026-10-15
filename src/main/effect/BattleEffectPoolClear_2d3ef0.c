#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_002d3ef0 {
    s32 m00;         /* +0x0 */
    s16 m04;         /* +0x4 */
    s16 m06;         /* +0x6 */
} Obj_FUN_002d3ef0;

void BattleEffectPoolClear_2d3ef0(Obj_FUN_002d3ef0 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m06 = 0;
}
