#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00340150 {
    u8 pad000[0x14];
    s16 m14;         /* +0x14 */
    s16 m16;         /* +0x16 */
} Obj_FUN_00340150;

void CaptionCfgSetImageSize_340150(Obj_FUN_00340150 *o, s16 p0, s16 p1)
{
    o->m14 = p0;
    o->m16 = p1;
}
