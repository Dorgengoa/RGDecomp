/* rgp:protos */
#define RGP_SELF_MapDataClearLoadState_1e7c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001e7c30 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    u8 pad00C[0x16];
    u8 m22;         /* +0x22 */
} Obj_FUN_001e7c30;

void MapDataClearLoadState_1e7c30(Obj_FUN_001e7c30 *o)
{
    o->m22 = 0;
    o->m00 = 0;
    o->m04 = 0;
    o->m08 = 0;
}
