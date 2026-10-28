/* rgp:protos */
#define RGP_SELF_CharaSetActionModeDamage_2190c0 1
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
    u8 pad000[0xA32];
    s16 mA32;
    u8 padA34[0x2];
    s16 mA36;
};

void CharaSetActionModeDamage_2190c0(struct Obj0 *p0)
{
    p0->mA32 = 0xF;
    CharaResetActionState_21ea00(p0);
    p0->mA36 = 0x19;
}
