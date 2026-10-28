/* rgp:protos */
#define RGP_SELF_AreaBoxSetCorner1_1e9790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001e9790 {
    u8 pad000[0xC];
    f32 m0C;         /* +0xC */
    f32 m10;         /* +0x10 */
    f32 m14;         /* +0x14 */
} Obj_FUN_001e9790;

void AreaBoxSetCorner1_1e9790(Obj_FUN_001e9790 *o, f32 f0, f32 f1, f32 f2)
{
    o->m0C = f0;
    o->m10 = f1;
    o->m14 = f2;
}
