/* rgp:protos */
#define RGP_SELF_MinimapSetBackdropPos_324a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00324a30 {
    u8 pad000[0xFC];
    s16 mFC;         /* +0xFC */
    s16 mFE;         /* +0xFE */
} Obj_FUN_00324a30;

void MinimapSetBackdropPos_324a30(Obj_FUN_00324a30 *o, s16 p0, s16 p1)
{
    o->mFC = p0;
    o->mFE = p1;
}
