#include "types.h"

extern void CharaResReleaseSounds_1effa0(s32 arg0);
extern void CharaResMgrSetMonSndLoad_1f0050(s32 arg0, s32 arg1);
extern s32 GetCharaResMgr_1fdb60(void);
extern s32 *GetGameData_1fede0(void);
extern void EventPlayerQueueEntry_250bd0(s32 arg0, s32 arg1, s32 arg2);
extern s32 ScriptGetInt_26a2a0(s32 arg0);
extern void LetterboxSetFade_277ea0(void *arg0, f32 arg1, f32 arg2, f32 arg3);
extern void LetterboxReset_278390(void *arg0);
extern void *GetLetterbox_27bd80(void);
extern void StateFlagSet_3ccb70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_0047E960;
extern void *D_00481F78;
extern s32 D_00482040;

s32 EvCmdEventPlayerQueueEntry_2610d0(s64 *arg0, s32 arg1)
{
    s32 *t;
    s32 a;
    s32 b;
    s32 c;
    s32 h;
    void *o;

    t = GetGameData_1fede0();
    StateFlagSet_3ccb70(t[4], 0x143, 0, 1);
    StateFlagSet_3ccb70(t[4], 0x7E4, 0, 1);
    if (D_00482040 == 0) {
        return 0;
    }
    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = 1;
    if (arg1 >= 2) {
        b = ScriptGetInt_26a2a0((s32)arg0++);
    }
    h = GetCharaResMgr_1fdb60();
    if (b != 0) {
        CharaResReleaseSounds_1effa0(h);
    }
    CharaResMgrSetMonSndLoad_1f0050(h, 0);
    EventPlayerQueueEntry_250bd0(D_00482040, a, 1);
    D_0047E960 = *(s32 *)((u8 *)D_00481F78 + 0x4344);
    if (arg1 < 2) {
        c = 1;
    } else {
        c = ScriptGetInt_26a2a0((s32)arg0);
    }
    if (c != 0) {
        o = GetLetterbox_27bd80();
        LetterboxReset_278390(o);
        *(s32 *)((u8 *)o + 0x18) = -0x20;
        LetterboxSetFade_277ea0(o, 1.0f, 10.0f, 0.0f);
    }
    return 1;
}
