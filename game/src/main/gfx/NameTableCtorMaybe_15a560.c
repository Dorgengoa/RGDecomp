/* rgp:protos */
#define RGP_SELF_NameTableCtorMaybe_15a560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    u8 pad010[0xC];
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    u8 pad030[0x19C];
    s32 m1CC;
    u8 pad1D0[0xC];
    s32 m1DC;
};

struct Obj0 *NameTableCtorMaybe_15a560(struct Obj0 *p0)
{
    p0->m24 = 0;
    p0->m20 = 0;
    p0->m2C = 0;
    p0->m28 = 0;
    p0->m1CC = 0;
    p0->m1DC = 0;
    p0->m0C = 0;
    p0->m1C = 0;
    return p0;
}
