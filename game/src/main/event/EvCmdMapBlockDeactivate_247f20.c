/* rgp:protos */
#define RGP_SELF_EvCmdMapBlockDeactivate_247f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 EvCmdMapBlockDeactivate_247f20(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    struct Obj0 * t0;
    s32 t1;

    r0 = ((s32)GetMapMgr_201a90());
    r1 = ScriptGetCodeAddr_249050(p0);
    r2 = MapSlotsFindBlockByName_1e4910(r0, r1, 0);
    if (r2 == 0) {
        return 0;
    }
    r3 = ((short)MapDataGetId_1e7bd0(r2));
    MapBlockIdListRemove_1e3310(r0, r3);
    t0 = gEventContext;
    t1 = gEventContext->m04;
    EventAreaListRemove_24a1e0((t1 + 0x60), r3);
    return 1;
}
