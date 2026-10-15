#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_002d6400 {
    u8 pad000[0x130];
    f32 m130;         /* +0x130 */
    f32 m134;         /* +0x134 */
    f32 m138;         /* +0x138 */
    f32 m13C;         /* +0x13C */
} Obj_FUN_002d6400;

void MovingLineSetUvRect_2d6400(Obj_FUN_002d6400 *o, f32 f0, f32 f1, f32 f2, f32 f3)
{
    o->m130 = f0;
    o->m134 = f1;
    o->m138 = f2;
    o->m13C = f3;
}
