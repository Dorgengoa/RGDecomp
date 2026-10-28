/* rgp:protos */
#define RGP_SELF_ActionWindowSet_228550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00228550 {
    f32 m00;         /* +0x0 */
    f32 m04;         /* +0x4 */
} Obj_FUN_00228550;

void ActionWindowSet_228550(Obj_FUN_00228550 *o, f32 f0, f32 f1)
{
    o->m00 = f0;
    o->m04 = f1;
}
