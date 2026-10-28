/* rgp:protos */
#define RGP_SELF_MesWinSelectChoice_271980 1
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
    u8 pad000[0x1C3C];
    s32 m1C3C;
};

s32 MesWinSelectChoice_271980(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = MesWinGetChoiceIndex_271b50(p0);
    if (r0 < 0) {
        p0->m1C3C = 0;
    }
    r1 = (MesWinSetChoiceIndex_271b60(p0, p1), (s32)0);
    return r1;
}
