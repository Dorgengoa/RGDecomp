#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern s32 MapLoadIsSettledMaybe_1e4e10(s32, s32);
extern s32 EventAreasLoading_24a140(s32, s32);
extern void ScriptSetRefInt_249030(s32, s32);

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
    r0 = GetMapMgr_201a90();
    r1 = MapLoadIsSettledMaybe_1e4e10(r0, 0) & 0xFF;
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
