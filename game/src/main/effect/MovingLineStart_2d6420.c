/* rgp:protos */
#define RGP_SELF_MovingLineStart_2d6420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x120];
    s16 m120;
    s16 m122;
    u8 pad124[0x4];
    s32 m128;
    u8 pad12C[0x4];
    s32 m130;
    s32 m134;
    s32 m138;
    s32 m13C;
    u8 pad140[0x6];
    s16 m146;
};

s32 MovingLineStart_2d6420(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 t0;

    p0->m120 = 1;
    p0->m128 = p1;
    p0->m122 = 0;
    r0 = GetGameMode_1f59c0();
    p0->m146 = r0;
    t0 = p0->m128;
    if (t0 > 0x10) {
        p0->m128 = 0x10;
    }
    p0->m130 = 0x42200000;
    p0->m134 = 0;
    p0->m138 = 0x41000000;
    p0->m13C = 0x42800000;
    return r0;
}
