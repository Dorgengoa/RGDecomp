/* rgp:protos */
#define RGP_SELF_MapDataSetColorF_1e7360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapDataSetColorF_1e7360(s32 p0, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    MapDataSetColor_1e72d0(p0, ((s32)(256.0f * fa0)), ((s32)(256.0f * fa0)), ((s32)(256.0f * fa0)), ((s32)(128.0f * (1.0f - fa3))));
}
