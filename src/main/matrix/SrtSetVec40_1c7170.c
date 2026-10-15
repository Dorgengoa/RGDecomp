#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001c7170 {
    u8 pad000[0x40];
    f32 m40;         /* +0x40 */
    f32 m44;         /* +0x44 */
    f32 m48;         /* +0x48 */
    s32 m4C;         /* +0x4C */
} Obj_FUN_001c7170;

void SrtSetVec40_1c7170(Obj_FUN_001c7170 *o, f32 f0, f32 f1, f32 f2)
{
    o->m40 = f0;
    o->m44 = f1;
    o->m48 = f2;
    o->m4C = 0;
}
