/* rgp:protos */
#define RGP_SELF_CaptionCfgSetGridDims_3401b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_003401b0 {
    u8 pad000[0xC];
    s16 m0C;         /* +0xC */
    s16 m0E;         /* +0xE */
} Obj_FUN_003401b0;

void CaptionCfgSetGridDims_3401b0(Obj_FUN_003401b0 *o, s16 p0, s16 p1)
{
    o->m0C = p0;
    o->m0E = p1;
}
