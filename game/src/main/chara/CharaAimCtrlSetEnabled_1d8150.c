/* rgp:protos */
#define RGP_SELF_CharaAimCtrlSetEnabled_1d8150 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
    u8 pad012[0x6];
    s32 m18;
};

void CharaAimCtrlSetEnabled_1d8150(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 t1;

    t0 = p0->m18;
    if (t0 != 0) {
        t1 = p0->m10;
        if (t1 != p1) {
            p0->m10 = p1;
        }
    }
}
