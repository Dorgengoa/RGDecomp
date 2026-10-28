/* rgp:protos */
#define RGP_SELF_MesSlot0Close_278e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

struct Obj0 *MesSlot0Close_278e40(void)
{
    s32 r0;
    struct Obj0 *r1;
    struct Obj0 * rv4;
    s32 t0;
    struct Obj0 * rv3;
    s32 r2;

    r0 = ((s32)GetMesMgr_277e90());
    r1 = MesMgrGetSlot_277a20(r0, 0);
    rv4 = (struct Obj0 *)r1;
    if (r1 != 0) {
        t0 = r1->m04;
        rv3 = (struct Obj0 *)r1;
        if (t0 != 0) {
            r2 = MesWinClose_2774f0(t0);
            rv3 = (struct Obj0 *)r2;
        }
        rv4 = (struct Obj0 *)rv3;
    }
    return rv4;
}
