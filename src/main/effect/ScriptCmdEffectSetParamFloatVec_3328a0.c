#include "types.h"

s32 EffectInstanceSetParamFloatVec_2dd640(s32, s32, f32 *);
f32 ScriptSlotGetFloat_334890(s32);
s32 ScriptSlotGetInt_3348b0(s32);
extern s32 D_004826E0;

s32 ScriptCmdEffectSetParamFloatVec_3328a0(s64 *arg0, s32 arg1)
{
    f32 sp[4];
    u8 *p;
    u32 n;
    s32 o;
    s32 r;

    if (arg1 < 4 || arg1 > 6) {
        return 0;
    }
    o = 0;
    switch (arg1) {
    case 4:
    case 5:
        o = D_004826E0;
        break;
    case 6:
        o = D_004826E0;
        break;
    }
    p = (u8 *)sp;
    n = 0x10;
    if (p != NULL) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    r = ScriptSlotGetInt_3348b0((s32)arg0++);
    sp[0] = ScriptSlotGetFloat_334890((s32)arg0++);
    sp[1] = ScriptSlotGetFloat_334890((s32)arg0++);
    sp[2] = ScriptSlotGetFloat_334890((s32)arg0++);
    if (arg1 > 4) {
        sp[3] = ScriptSlotGetFloat_334890((s32)arg0);
    }
    EffectInstanceSetParamFloatVec_2dd640(o, r, sp);
    return 1;
}
