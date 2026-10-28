/* rgp:protos */
#define RGP_SELF_FixCameraRecArraySet_189760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00189760 {
    u8 pad000[0x1630];
    s32 m1630;         /* +0x1630 */
    s32 m1634;         /* +0x1634 */
} Obj_FUN_00189760;

void FixCameraRecArraySet_189760(Obj_FUN_00189760 *o, s32 p0, s32 p1)
{
    o->m1630 = p1;
    o->m1634 = p0;
}
