/* rgp:protos */
#define RGP_SELF_EntrySetGridSize_323bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00323bd0 {
    u8 pad000[0x18];
    s32 m18;         /* +0x18 */
    s32 m1C;         /* +0x1C */
} Obj_FUN_00323bd0;

void EntrySetGridSize_323bd0(Obj_FUN_00323bd0 *o, s32 p0, s32 p1)
{
    o->m18 = p0;
    o->m1C = p1;
}
