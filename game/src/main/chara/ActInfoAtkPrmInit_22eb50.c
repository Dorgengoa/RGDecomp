/* rgp:protos */
#define RGP_SELF_ActInfoAtkPrmInit_22eb50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0022eb50 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s32 m04;         /* +0x4 */
} Obj_FUN_0022eb50;

void ActInfoAtkPrmInit_22eb50(Obj_FUN_0022eb50 *o, s16 p0, s16 p1, s32 p2)
{
    o->m00 = p0;
    o->m02 = p1;
    o->m04 = p2;
}
