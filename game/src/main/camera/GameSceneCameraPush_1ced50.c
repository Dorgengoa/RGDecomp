/* rgp:protos */
#define RGP_SELF_GameSceneCameraPush_1ced50 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4344];
    s32 m4344;
    u8 pad4348[0x1A94];
    s32 arr5DDC[8];
    s32 m5DFC;
};

void GameSceneCameraPush_1ced50(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 t2;

    t0 = p0->m5DFC;
    if (t0 != 8) {
        t1 = p0->m4344;
        p0->arr5DDC[t0] = t1;
        t2 = p0->m5DFC;
        p0->m5DFC = (t2 + 1);
        return;
    }
}
