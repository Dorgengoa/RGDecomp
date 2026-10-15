#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_003fdac0 {
    s64 m00;         /* +0x0 */
    s64 m08;         /* +0x8 */
} Obj_FUN_003fdac0;

void RankingHolderClear_3fdac0(Obj_FUN_003fdac0 *o)
{
    o->m00 = 0;
    o->m08 = 0;
}
