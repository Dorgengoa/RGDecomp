/* rgp:protos */
#define RGP_SELF_CharaEffectClear_2143d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045CA60[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x424];
    s16 m424;
    u8 pad426[0x2];
    s32 m428;
};

void CharaEffectClear_2143d0(struct Obj0 *p0)
{
    s32 t0;
    s16 t1;

    t0 = p0->m428;
    if (t0 != 0) {
        t1 = p0->m424;
        ActCfgTableRunEvntByName_21f680(t0, t1, D_0045CA60);
    }
}
