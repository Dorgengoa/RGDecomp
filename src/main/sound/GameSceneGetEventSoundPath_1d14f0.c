#include "types.h"

extern void * GameSceneSoundEnvFindPreset_1d1540(s32, s32);
extern void SoundEventPathFormat_1d2290(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1E];
    s16 m1E;
    s16 m20;
};

s32 GameSceneGetEventSoundPath_1d14f0(s32 p0, s32 p1, s32 p2)
{
    struct Obj0 *r0;
    s16 t0;
    s16 t1;

    r0 = GameSceneSoundEnvFindPreset_1d1540(p0, p2);
    if (r0 == 0) {
        return 0;
    }
    t0 = r0->m1E;
    t1 = r0->m20;
    SoundEventPathFormat_1d2290(p1, t0, t1);
    return 1;
}
