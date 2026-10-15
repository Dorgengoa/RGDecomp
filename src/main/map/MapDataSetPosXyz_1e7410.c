#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001e7410 {
    u8 pad000[0x30];
    f32 m30;         /* +0x30 */
    f32 m34;         /* +0x34 */
    f32 m38;         /* +0x38 */
} Obj_FUN_001e7410;

void MapDataSetPosXyz_1e7410(Obj_FUN_001e7410 *o, f32 f0, f32 f1, f32 f2)
{
    o->m30 = f0;
    o->m34 = f1;
    o->m38 = f2;
}
