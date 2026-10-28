/* rgp:protos */
#define RGP_SELF_CharaSysStateGetBattlePosMaybe_3a3840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x238];
    s32 m238;
};

struct Obj1 {
    s32 m00;
    s32 m04;
    s32 m08;
};

void CharaSysStateGetBattlePosMaybe_3a3840(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;

    t0 = p0->m238;
    if (t0 != 0) {
        CharaStateCopyPosMaybe_3a7990(t0, p1);
    } else {
        p1->m00 = 0;
        p1->m04 = 0;
        p1->m08 = 0;
    }
}
