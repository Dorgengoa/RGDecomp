/* rgp:protos */
#define RGP_SELF_EvCmdAreasReadyMaybe_248ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

extern struct Obj0 *gEventContext;

s32 EvCmdAreasReadyMaybe_248ac0(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv;
    s32 ok;

    if (p1 <= 0) {
        return 0;
    }
    rv = 1;
    r0 = ((s32)GetMapMgr_201a90());
    r1 = ((unsigned char)MapLoadIsSettledMaybe_1e4e10(r0, 0)) & 0xFF;
    r2 = EventAreasLoading_24a140((gEventContext->m04 + 0x60), r0);
    ok = (r2 != 0);
    if (r1 != 0) {
        if (ok == 0) {
            rv = 0;
        }
    }
    ScriptSetRefInt_249030(p0, rv);
    return 1;
}
