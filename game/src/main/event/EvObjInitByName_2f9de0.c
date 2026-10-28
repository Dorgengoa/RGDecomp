/* rgp:protos */
#define RGP_SELF_EvObjInitByName_2f9de0 1
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
struct Obj1;

struct Obj0 {
    u8 pad000[0xD0];
    s32 mD0;
    u8 pad0D4[0x4];
    s32 mD8;
};

struct Obj1 {
    s8 m00;
};

void EvObjInitByName_2f9de0(struct Obj0 *p0, s32 p1, s32 p2, struct Obj1 *p3)
{
    s8 t0;
    s32 r2;
    s32 r3;

    EvObjReset_2f9eb0(p0);
    EventRecInitWithKey_2e5800(p0, p1);
    p0->mD0 = p2;
    if (p3 != 0) {
        t0 = p3->m00;
        if (t0 == 0) {
            return;
        }
        r2 = ((s32)GetEventObjMgr_2d1960());
        r3 = ((s32)EventObjMgrFindScriptRecByName_2e9a20(r2, p3));
        p0->mD8 = r3;
        return;
    }
}
