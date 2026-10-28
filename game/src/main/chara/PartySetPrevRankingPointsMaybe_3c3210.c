/* rgp:protos */
#define RGP_SELF_PartySetPrevRankingPointsMaybe_3c3210 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00465BE0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x184];
    s32 m184;
};

void PartySetPrevRankingPointsMaybe_3c3210(struct Obj0 *p0, s32 p1)
{
    s32 t0;

    p0->m184 = p1;
    if (p1 < 0) {
        p0->m184 = 0;
    } else {
        t0 = D_00465BE0;
        if (t0 < p1) {
            p0->m184 = t0;
        }
    }
}
