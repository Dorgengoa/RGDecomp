/* rgp:protos */
#define RGP_SELF_MenuObjSetBattlePartner_387ca0 1
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
    u8 pad000[0x9C4];
    s32 m9C4;
};

void MenuObjSetBattlePartner_387ca0(struct Obj0 *p0, s32 p1)
{
    p0->m9C4 = p1;
    if (p1 != 0) {
        BitArraySetReturnOld_384360((struct Obj0 *)((u8 *)p0 + 0x986), 3, 1);
    } else {
        BitArraySetReturnOld_384360((struct Obj0 *)((u8 *)p0 + 0x986), 3, 0);
    }
}
