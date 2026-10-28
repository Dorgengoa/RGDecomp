/* rgp:protos */
#define RGP_SELF_EvSwitchRecSetPos_2f8830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_002f8830 {
    u8 pad000[0x18];
    f32 m18;         /* +0x18 */
    f32 m1C;         /* +0x1C */
    f32 m20;         /* +0x20 */
} Obj_FUN_002f8830;

void EvSwitchRecSetPos_2f8830(Obj_FUN_002f8830 *o, f32 f0, f32 f1, f32 f2)
{
    o->m18 = f0;
    o->m1C = f1;
    o->m20 = f2;
}
