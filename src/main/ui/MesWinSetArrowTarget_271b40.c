#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00271b40 {
    u8 pad000[0x1C28];
    s32 m1C28;         /* +0x1C28 */
    s32 m1C2C;         /* +0x1C2C */
} Obj_FUN_00271b40;

void MesWinSetArrowTarget_271b40(Obj_FUN_00271b40 *o, s32 p0, s32 p1)
{
    o->m1C28 = p0;
    o->m1C2C = p1;
}
