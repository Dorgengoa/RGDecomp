/* rgp:protos */
#define RGP_SELF_CharaSetMp_3b7fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s16 m18;
    u8 pad01A[0xC];
    u16 m26;
};

void CharaSetMp_3b7fd0(struct Obj0 *p0, s32 p1)
{
    if (p1 <= 0) {
        p0->m18 = 0;
    } else {
        if (p1 >= p0->m26) {
            p0->m18 = p0->m26;
        } else {
            p0->m18 = p1;
        }
    }
}
