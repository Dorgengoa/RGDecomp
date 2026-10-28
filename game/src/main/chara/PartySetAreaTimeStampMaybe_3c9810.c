/* rgp:protos */
#define RGP_SELF_PartySetAreaTimeStampMaybe_3c9810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xE8];
    s16 mE8;
    u8 pad0EA[0x6];
    s64 mF0;
    u8 pad0F8[0xBC];
    s16 m1B4;
    u8 pad1B6[0x2];
    s64 m1B8;
};

s32 PartySetAreaTimeStampMaybe_3c9810(struct Obj0 *p0, s32 p1, s64 p2)
{
    p0->mE8 = p1;
    p0->mF0 = p2;
    p0->m1B4 = p0->mE8;
    p0->m1B8 = p0->mF0;
    return 1;
}
