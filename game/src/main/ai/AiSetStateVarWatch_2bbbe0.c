/* rgp:protos */
#define RGP_SELF_AiSetStateVarWatch_2bbbe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x13A];
    u8 m13A;
    u8 m13B;
};

void AiSetStateVarWatch_2bbbe0(struct Obj0 *p0, s32 p1, s32 p2)
{
    if (p1 != 0) {
        p0->m13A = p2;
        p0->m13B = 0xFF;
    } else {
        p0->m13A = 0xFF;
    }
}
