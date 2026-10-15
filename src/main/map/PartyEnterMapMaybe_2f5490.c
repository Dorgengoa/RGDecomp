#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 MapSlotsFindBlockIdByName_1e44f0(s32, s32, s32);
extern void PartySetMapId_3c9cc0(s32, s32);
extern void SceneSoundEnvApplyPreset_207e20(s32, s32);
extern void BgmPlayTrackIfChangedMaybe_207880(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

void PartyEnterMapMaybe_2f5490(s32 p0, s32 p1, s32 p2)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;
    s32 t0;

    r0 = GetGameData_1fede0();
    r1 = GetMapMgr_201a90();
    r2 = MapSlotsFindBlockIdByName_1e44f0(r1, p0, 0);
    t0 = r0->m18;
    PartySetMapId_3c9cc0(t0, r2);
    SceneSoundEnvApplyPreset_207e20(p1, 0);
    BgmPlayTrackIfChangedMaybe_207880(p2, 1);
}
