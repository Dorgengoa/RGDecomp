#include "types.h"

struct E8 { s32 a; s32 b; };

extern s32 StreamPlayAllowedMaybe_2f5210(void);
extern s32 ScriptSetRefInt_26a1e0(struct E8 *, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 ScriptGetInt_26a2a0(struct E8 *);
extern s32 StreamGetChanStatus_1cd930(s32, s32);

s32 EvCmdVoiceStreamStateMaybe_25ccb0(struct E8 *p0)
{
    struct E8 *q;
    s32 r0;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 rv6;

    q = p0;
    r0 = StreamPlayAllowedMaybe_2f5210();
    if (r0 == 0) {
        ScriptSetRefInt_26a1e0(q, 1);
        return 1;
    }
    r2 = GetLoaderMgr_1f59d0();
    r3 = ScriptGetInt_26a2a0(q++);
    r4 = StreamGetChanStatus_1cd930(r2, r3);
    rv6 = 0;
    if (r4 == 2) {
        rv6 = 1;
    } else if (r4 == -2) {
        rv6 = -1;
    }
    ScriptSetRefInt_26a1e0(q, rv6);
    return 1;
}
