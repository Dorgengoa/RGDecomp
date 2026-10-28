/* rgp:protos */
#define RGP_SELF_MenuObjSetBreedPartner_387c50 1
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
    u8 pad000[0x9C8];
    s32 m9C8;
};

void MenuObjSetBreedPartner_387c50(struct Obj0 *p0, s32 p1)
{
    p0->m9C8 = p1;
    if (p1 != 0) {
        BitArraySetReturnOld_384360((struct Obj0 *)((u8 *)p0 + 0x986), 1, 1);
    } else {
        BitArraySetReturnOld_384360((struct Obj0 *)((u8 *)p0 + 0x986), 1, 0);
    }
}
