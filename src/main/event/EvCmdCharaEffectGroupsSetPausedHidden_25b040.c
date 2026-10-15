#include "types.h"
typedef struct { s32 a, b; } E8_25B040;
extern s32 ScriptGetInt_26a2a0(E8_25B040 *);
extern void CharaEffectGroupsSetPausedHiddenAll_27a260(s32, s32, s32);
extern void CharaEffectGroupsSetPausedHidden_27a300(s32, s32, s32, s32);

s32 EvCmdCharaEffectGroupsSetPausedHidden_25b040(E8_25B040 *p0, s32 p1)
{
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = ScriptGetInt_26a2a0(p0++);
    b = ScriptGetInt_26a2a0(p0++);
    c = ScriptGetInt_26a2a0(p0++);
    d = -1;
    if (p1 >= 4) {
        d = ScriptGetInt_26a2a0(p0);
    }
    if (a < 0) {
        CharaEffectGroupsSetPausedHiddenAll_27a260(b != 0, c != 0, d);
    } else {
        CharaEffectGroupsSetPausedHidden_27a300(a, b != 0, c != 0, d);
    }
    return 1;
}
