/* rgp:protos */
#define RGP_SELF_GameDataInit_3ee5b0 1
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
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    u8 pad02C[0x2];
    s16 m2E;
    s16 m30;
};

void GameDataInit_3ee5b0(struct Obj0 *p0)
{
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m20 = 0;
    p0->m24 = 0;
    p0->m28 = 0;
    p0->m2E = 0;
    p0->m30 = 0;
    GameDataReset_3ee0e0(p0);
}
