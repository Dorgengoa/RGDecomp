/* rgp:protos */
#define RGP_SELF_EventRefListInit_304950 1
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
    s32 m08;
};

s32 EventRefListInit_304950(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 r1;
    s32 r2;

    EventRefListReset_3049c0(p0);
    p0->m04 = p2;
    p0->m08 = p3;
    r1 = ((s32)GetEventObjMgr_2d1960());
    r2 = ((s32)EventObjMgrFindPathRecByName_2e9c90(r1, p1));
    p0->m00 = r2;
    return r2;
}
