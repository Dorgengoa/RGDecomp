#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00340210 {
    u8 pad000[0x4];
    s16 m04;         /* +0x4 */
    s16 m06;         /* +0x6 */
} Obj_FUN_00340210;

void CaptionCfgSetCellSize_340210(Obj_FUN_00340210 *o, s16 p0, s16 p1)
{
    o->m04 = p0;
    o->m06 = p1;
}
