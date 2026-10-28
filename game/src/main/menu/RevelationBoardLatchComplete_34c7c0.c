/* rgp:protos */
#define RGP_SELF_RevelationBoardLatchComplete_34c7c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x76E];
    s16 m76E;
    u8 pad770[0x30];
    s16 m7A0;
};

s16 RevelationBoardLatchComplete_34c7c0(struct Obj0 *p0)
{
    s32 rv0;

    if (p0->m76E == 6) {
        rv0 = p0->m7A0;
        if (p0->m7A0 == 0) {
            p0->m7A0 = 1;
            rv0 = 1;
        }
    }
    return p0->m7A0;
}
