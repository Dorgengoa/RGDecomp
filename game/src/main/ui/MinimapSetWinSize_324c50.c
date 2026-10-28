/* rgp:protos */
#define RGP_SELF_MinimapSetWinSize_324c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00324c50 {
    u8 pad000[0x112];
    s16 m112;         /* +0x112 */
    s16 m114;         /* +0x114 */
} Obj_FUN_00324c50;

void MinimapSetWinSize_324c50(Obj_FUN_00324c50 *o, s16 p0, s16 p1)
{
    o->m112 = p0;
    o->m114 = p1;
}
