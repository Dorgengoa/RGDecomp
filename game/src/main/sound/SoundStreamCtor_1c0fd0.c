/* rgp:protos */
#define RGP_SELF_SoundStreamCtor_1c0fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    u8 m1C;
    u8 m1D;
    u8 m1E;
    u8 pad01F[0x19];
    s32 m38;
    s32 m3C;
    s32 m40;
    s8 m44;
    u8 m45;
    u8 pad046[0x2];
    u8 m48;
    u8 pad049[0x3];
    s32 m4C;
    s32 m50;
    u8 pad054[0x10];
    s32 m64;
    s32 m68;
    s32 m6C;
    s32 m70;
    u8 m74;
    u8 pad075[0x3];
    s32 m78;
};

struct Obj0 *SoundStreamCtor_1c0fd0(struct Obj0 *p0)
{
    p0->m04 = 0x800;
    p0->m10 = -1;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m1E = 0;
    p0->m1D = 0;
    p0->m3C = -1;
    p0->m40 = -1;
    p0->m48 = 1;
    p0->m4C = 0;
    p0->m50 = 0;
    p0->m00 = -1;
    p0->m70 = 0;
    p0->m38 = -1;
    p0->m44 = -1;
    p0->m48 = 1;
    p0->m4C = 0;
    p0->m50 = 0;
    p0->m64 = 0;
    p0->m6C = 0;
    p0->m45 = 0;
    p0->m68 = 0;
    p0->m74 = 0;
    p0->m78 = 0;
    return p0;
}
