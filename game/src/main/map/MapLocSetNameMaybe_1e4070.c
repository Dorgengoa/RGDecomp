/* rgp:protos */
#define RGP_SELF_MapLocSetNameMaybe_1e4070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void strcpy(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    u8 m0C;
    u8 pad00D[0x1F];
    s16 m2C;
    s16 m2E;
};

void MapLocSetNameMaybe_1e4070(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    p0->m0C = 0;
    if (p1 != 0) {
        strcpy((struct Obj0 *)((u8 *)p0 + 0xC), p1);
    }
    p0->m2C = p2;
    p0->m2E = p3;
}
