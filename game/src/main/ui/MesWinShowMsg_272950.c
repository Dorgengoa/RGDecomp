/* rgp:protos */
#define RGP_SELF_MesWinShowMsg_272950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x194C];
    s32 m194C;
};

void MesWinShowMsg_272950(struct Obj0 *p0, s32 p1)
{
    s32 t0;

    if (p1 >= 0) {
        t0 = p0->m194C;
        if (t0 == p1) {
            MesWinAdvance_2768f0(p0);
            return;
        }
        p0->m194C = p1;
        MesWinResetLayout_2729c0(p0);
        MesWinMeasureMsg_273470(p0, p1);
        MesWinLayoutMsg_273cf0(p0, p1);
        return;
    }
}
