/* rgp:protos */
#define RGP_SELF_EvObjLiftReset_336500 1
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
    u8 pad000[0xE0];
    s32 mE0;
    s32 mE4;
    s16 mE8;
    s16 mEA;
    s32 mEC;
    s32 mF0;
    s32 mF4;
    u8 mF8;
    u8 pad0F9[0xF];
    s16 m108;
    s16 m10A;
    s16 m10C;
};

void EvObjLiftReset_336500(struct Obj0 *p0)
{
    EvObjReset_2f9eb0(p0);
    p0->mEC = 0;
    p0->mF0 = 0;
    p0->mE0 = 0;
    p0->mE8 = 0;
    p0->mE4 = 0;
    p0->mEA = 0;
    p0->mF8 = 0;
    p0->m108 = 0;
    p0->m10A = 0;
    p0->m10C = -1;
    p0->m10C = -1;
    p0->mF4 = 0;
}
