/* rgp:protos */
#define RGP_SELF_MapCfgFarClip_18c7e0 1
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

extern s32 D_00481254;

s32 MapCfgFarClip_18c7e0(s32 p0, s32 p1)
{
    s32 t0;
    s32 rv4;
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    t0 = D_00481254;
    rv4 = rv3;
    if (t0 == 0) {
        rv4 = 0;
    } else {
        r0 = ListNodeGetData_18a370(t0);
        rv3 = 1;
        if (r0 == 0) {
            rv3 = 0;
        } else {
            r1 = ((s32)NodeGetFarClip_18bc20(r0));
            r2 = (FarClipRecParseArgs_18c850(r1, p0, p1), (s32)0);
            rv3 = 1;
        }
        rv4 = rv3;
    }
    return rv4;
}
