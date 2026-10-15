#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00311870 {
    u8 pad000[0x14];
    s32 m14;         /* +0x14 */
    u8 pad018[0x2];
    s16 m1A;         /* +0x1A */
} Obj_FUN_00311870;

void NavNodeSetEdges_311870(Obj_FUN_00311870 *o, s32 p0, s16 p1)
{
    o->m14 = p0;
    o->m1A = p1;
}
