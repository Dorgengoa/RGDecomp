#include "types.h"

extern void CharaGetPos_2388a0(s32, void *);
extern void VecSub_1cbd00(void *, s32, void *);
extern void CharaSetDirNormalizedMaybe_213b30(s32, void *);
extern s32 CharaSetMoveDirMaybe_213b00(s32, void *);
extern s32 AiSetSpeedScale_2c0ec0(s32, f32);
extern void AiSetSpeedCapScale_2c0eb0(s32, f32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

void AiMoveFaceTarget_2be560(s32 p0, struct Obj0 *p1, s32 p2)
{
    u128 v50;
    u128 v40;
    s32 t0;
    s32 r3;
    s32 r4;

    t0 = p1->m00;
    CharaGetPos_2388a0(t0, &v50);
    VecSub_1cbd00(&v40, p2, &v50);
    CharaSetDirNormalizedMaybe_213b30(t0, &v40);
    r3 = CharaSetMoveDirMaybe_213b00(t0, &v40);
    r4 = AiSetSpeedScale_2c0ec0(p0, 1.0f);
    AiSetSpeedCapScale_2c0eb0(p0, 0.25f);
}
