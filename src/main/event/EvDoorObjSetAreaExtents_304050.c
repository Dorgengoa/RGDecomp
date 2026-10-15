#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00304050 {
    u8 pad000[0x170];
    f32 m170;         /* +0x170 */
    f32 m174;         /* +0x174 */
    f32 m178;         /* +0x178 */
} Obj_FUN_00304050;

void EvDoorObjSetAreaExtents_304050(Obj_FUN_00304050 *o, f32 f0, f32 f1, f32 f2)
{
    o->m170 = f0;
    o->m174 = f1;
    o->m178 = f2;
}
