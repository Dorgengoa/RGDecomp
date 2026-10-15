#include "types.h"

f32 TaggedGetFloat_2490d0(s32);
s32 ScriptGetInt_2490f0(s32);
s32 MenuWinGet_2653e0(s32);
s32 MenuWinSetColor_26c380(s32, f32 *);

s32 EvCmdMenuWinSetColor_243700(s64 *arg0) {
    f32 v[4];
    s32 h;

    h = MenuWinGet_2653e0(ScriptGetInt_2490f0((s32)arg0++));
    if (h == 0) {
        return 0;
    }
    switch (*(s32 *)arg0) {
    case 0:
        v[0] = ScriptGetInt_2490f0((s32)arg0++);
        v[1] = ScriptGetInt_2490f0((s32)arg0++);
        v[2] = ScriptGetInt_2490f0((s32)arg0++);
        v[3] = ScriptGetInt_2490f0((s32)arg0);
        break;
    case 1:
        v[0] = TaggedGetFloat_2490d0((s32)arg0++);
        v[1] = TaggedGetFloat_2490d0((s32)arg0++);
        v[2] = TaggedGetFloat_2490d0((s32)arg0++);
        v[3] = TaggedGetFloat_2490d0((s32)arg0);
        break;
    }
    MenuWinSetColor_26c380(h, v);
    return 1;
}
