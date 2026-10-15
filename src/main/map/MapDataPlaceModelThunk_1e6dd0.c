#include "types.h"

extern void MapDataPlaceModel_1e6dd0(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapDataPlaceModelThunk_1e6dd0(s32 p0, s32 p1, f32 fa0)
{
    MapDataPlaceModel_1e6dd0(p0, p1, fa0);
}
