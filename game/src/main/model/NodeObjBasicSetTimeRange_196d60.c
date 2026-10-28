/* rgp:protos */
#define RGP_SELF_NodeObjBasicSetTimeRange_196d60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00196d60 {
    u8 pad000[0x84];
    f32 m84;         /* +0x84 */
    f32 m88;         /* +0x88 */
} Obj_FUN_00196d60;

void NodeObjBasicSetTimeRange_196d60(Obj_FUN_00196d60 *o, f32 f0, f32 f1)
{
    o->m84 = f0;
    o->m88 = f1;
}
