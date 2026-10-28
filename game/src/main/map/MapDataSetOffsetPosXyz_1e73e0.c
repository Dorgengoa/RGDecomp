/* rgp:protos */
#define RGP_SELF_MapDataSetOffsetPosXyz_1e73e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001e73e0 {
    u8 pad000[0x40];
    f32 m40;         /* +0x40 */
    f32 m44;         /* +0x44 */
    f32 m48;         /* +0x48 */
} Obj_FUN_001e73e0;

void MapDataSetOffsetPosXyz_1e73e0(Obj_FUN_001e73e0 *o, f32 f0, f32 f1, f32 f2)
{
    o->m40 = f0;
    o->m44 = f1;
    o->m48 = f2;
}
