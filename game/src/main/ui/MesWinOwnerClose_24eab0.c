/* rgp:protos */
#define RGP_SELF_MesWinOwnerClose_24eab0 1
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
    u8 pad000[0xC];
    s32 m0C;
    u8 pad010[0xC];
    s32 m1C;
};

int MesWinOwnerClose_24eab0(struct Obj0 *p0)
{ int rgp_v0 = 0;
    s32 t0;

    t0 = p0->m0C;
    (rgp_v0 = MesWinClose_2774f0(t0));
    p0->m1C = 1;
return rgp_v0; }
