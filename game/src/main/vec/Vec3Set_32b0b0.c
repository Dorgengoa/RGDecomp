/* rgp:protos */
#define RGP_SELF_Vec3Set_32b0b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0032b0b0 {
    f32 m00;         /* +0x0 */
    f32 m04;         /* +0x4 */
    f32 m08;         /* +0x8 */
} Obj_FUN_0032b0b0;

void Vec3Set_32b0b0(Obj_FUN_0032b0b0 *o, f32 f0, f32 f1, f32 f2)
{
    o->m00 = f0;
    o->m04 = f1;
    o->m08 = f2;
}
