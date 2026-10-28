/* rgp:protos */
#define RGP_SELF_EvM05ChangeSetVolumeRecs_352050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00352050 {
    u8 pad000[0xE0];
    s32 mE0;         /* +0xE0 */
    s32 mE4;         /* +0xE4 */
} Obj_FUN_00352050;

void EvM05ChangeSetVolumeRecs_352050(Obj_FUN_00352050 *o, s32 p0, s32 p1)
{
    o->mE0 = p0;
    o->mE4 = p1;
}
