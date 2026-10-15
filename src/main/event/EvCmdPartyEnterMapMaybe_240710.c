#include "types.h"

struct S8 { s32 a; s32 b; };

extern s32 SysModeMsgIsWarpStart_2f5510(void);
extern s32 ScriptGetCodeAddr_249050(struct S8 *);
extern s32 ScriptGetInt_2490f0(struct S8 *);
extern void PartyEnterMapMaybe_2f5490(s32, s32, s32);

s32 EvCmdPartyEnterMapMaybe_240710(struct S8 *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = SysModeMsgIsWarpStart_2f5510();
    if (r0 == 0) {
        return 1;
    }
    r1 = ScriptGetCodeAddr_249050(p0++);
    r2 = ScriptGetInt_2490f0(p0++);
    r3 = ScriptGetInt_2490f0(p0);
    PartyEnterMapMaybe_2f5490(r1, r2, r3);
    return 1;
}
