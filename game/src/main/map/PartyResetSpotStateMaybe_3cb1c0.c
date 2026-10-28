/* rgp:protos */
#define RGP_SELF_PartyResetSpotStateMaybe_3cb1c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_00465940;

struct Obj0;

struct Obj0 {
    u8 pad000[0x118];
    s64 m118;
    s32 m120;
    s32 m124;
    f32 m128;
    f32 m12C;
    f32 m130;
    f32 m134;
    s32 m138;
    s16 m13C;
    u8 pad13E[0x2];
    s32 m140;
    u8 pad144[0xC];
    s32 m150;
    s32 m154;
    s32 m158;
    s32 m15C;
};

void PartyResetSpotStateMaybe_3cb1c0(struct Obj0 *p0)
{
    f32 t0;

    p0->m118 = 0;
    t0 = D_00465940;
    p0->m120 = 0;
    p0->m124 = 0;
    p0->m128 = t0;
    p0->m12C = t0;
    p0->m130 = t0;
    p0->m134 = t0;
    p0->m138 = 0x41300000;
    p0->m13C = 0;
    p0->m140 = 0;
    p0->m150 = 0;
    p0->m154 = 0;
    p0->m158 = 0;
    p0->m15C = 0;
}
