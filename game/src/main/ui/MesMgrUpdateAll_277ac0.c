/* rgp:protos */
#define RGP_SELF_MesMgrUpdateAll_277ac0 1
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
    u8 pad000[0x1E20];
    s32 m1E20;
};

void MesMgrUpdateAll_277ac0(struct Obj0 *p0)
{
    s32 t0;
    s32 l0;
    s32 l1;
    s32 t1;

    t0 = p0->m1E20;
    if ((t0 & 1) != 0) {
        l0 = (t0 & 1);
        l1 = 0;
        do {
            t1 = *(s32 *)((u8 *)p0 + (l1 << 2) + 0x1E00);
            if (t1 != 0) {
                MesSlotUpdate_277da0(t1);
            }
            l0 = ((l1 + 1) < 8);
            l1 = (l1 + 1);
        } while (l0 != 0);
        return;
    }
}
