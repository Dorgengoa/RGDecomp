#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00340180 {
    u8 pad000[0x10];
    s16 m10;         /* +0x10 */
    s16 m12;         /* +0x12 */
} Obj_FUN_00340180;

void CaptionCfgSetAltGridDims_340180(Obj_FUN_00340180 *o, s16 p0, s16 p1)
{
    o->m10 = p0;
    o->m12 = p1;
}
