/* rgp:protos */
#define RGP_SELF_GameSceneSoundRevTableSet_1d19f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memcpy(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA61C];
    s32 mA61C;
};

void GameSceneSoundRevTableSet_1d19f0(struct Obj0 *p0, s32 p1, s32 p2)
{
    p0->mA61C = (((u32)p2) >> 3);
    memcpy((struct Obj0 *)((u8 *)p0 + 0xA620), p1, p2);
}
