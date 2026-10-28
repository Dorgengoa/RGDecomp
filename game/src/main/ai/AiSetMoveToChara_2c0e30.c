/* rgp:protos */
#define RGP_SELF_AiSetMoveToChara_2c0e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x288];
    s32 m288;
    s32 m28C;
    s32 m290;
    s32 m294;
};

void AiSetMoveToChara_2c0e30(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    p0->m288 = 2;
    p0->m28C = p1;
    p0->m294 = 0;
    p0->m290 = p2;
    if (p2 < 0) {
        AiSetNoTimeout_2c11a0(p0, 1);
    }
    AiSetTargetCharaId_2c0f10(p0, p3);
}
