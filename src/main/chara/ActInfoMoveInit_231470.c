#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00231470 {
    s32 m00;         /* +0x0 */
    f32 m04;         /* +0x4 */
    f32 m08;         /* +0x8 */
    f32 m0C;         /* +0xC */
} Obj_FUN_00231470;

void ActInfoMoveInit_231470(Obj_FUN_00231470 *o, s32 p0, f32 f0, f32 f1, f32 f2)
{
    o->m00 = p0;
    o->m08 = f1;
    o->m04 = f0;
    o->m0C = f2;
}
