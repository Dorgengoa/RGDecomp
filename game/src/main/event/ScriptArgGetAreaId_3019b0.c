/* rgp:protos */
#define RGP_SELF_ScriptArgGetAreaId_3019b0 1
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
    s32 m00;
    s32 m04;
};

s32 ScriptArgGetAreaId_3019b0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv3;
    s32 r0;
    s32 t1;
    s32 r1;
    s32 r2;

    t0 = p0->m00;
    rv3 = r2;
    if (t0 == 0) {
        r0 = ((s32)GetMapMgr_201a90());
        t1 = p0->m04;
        r1 = MapSlotsFindIdByName_1e4520(r0, t1);
        rv3 = r1;
    } else {
        r2 = ScriptArgGetInt_301a60(p0);
        rv3 = r2;
    }
    return rv3;
}
