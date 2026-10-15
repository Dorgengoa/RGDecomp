#include "types.h"

extern s32 MapSlotsFindById_1e4b90(s32, s32, s32);
extern void MapDataGetSoundEnvPresetId_1e5340(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapGetSoundEnvPresetIdById_1e53f0(s32 p0, s32 p1)
{
    s32 r0;

    r0 = MapSlotsFindById_1e4b90(p0, p1, 0);
    MapDataGetSoundEnvPresetId_1e5340(p0, r0);
}
