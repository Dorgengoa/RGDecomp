#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001c73d0 {
    u8 pad000[0x10];
    f32 m10;         /* +0x10 */
    f32 m14;         /* +0x14 */
    f32 m18;         /* +0x18 */
    s32 m1C;         /* +0x1C */
} Obj_FUN_001c73d0;

void SrtSetRot_1c73d0(Obj_FUN_001c73d0 *o, f32 f0, f32 f1, f32 f2)
{
    o->m10 = f0;
    o->m14 = f1;
    o->m18 = f2;
    o->m1C = 0;
}
