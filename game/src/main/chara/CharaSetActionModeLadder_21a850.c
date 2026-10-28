/* rgp:protos */
#define RGP_SELF_CharaSetActionModeLadder_21a850 1
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
    u8 pad000[0xA32];
    s16 mA32;
};

void CharaSetActionModeLadder_21a850(struct Obj0 *p0)
{
    p0->mA32 = 7;
    CharaResetActionState_21ea00(p0);
    CharaMoveReqResetThunk_2194d0((struct Obj0 *)((u8 *)p0 + 0x930));
}
