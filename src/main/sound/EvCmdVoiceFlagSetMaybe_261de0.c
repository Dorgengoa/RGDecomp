#include "types.h"

extern s32 ScriptCmdStubRelated_261e70(s32 arg0, s32 arg1);
extern s32 ScriptGetInt_26a2a0(s32 arg0);
extern u8 D_004BDA20[0x400];

s32 EvCmdVoiceFlagSetMaybe_261de0(s64 *arg0, s32 arg1)
{
    (*(s32 *)D_004BDA20) = 1;
    ScriptGetInt_26a2a0((s32)arg0++);
    switch (arg1) {
    case 1:
        return ScriptCmdStubRelated_261e70(1, 0x7FFF);
    case 2:
        return ScriptCmdStubRelated_261e70(1, ScriptGetInt_26a2a0((s32)arg0));
    default:
        return 0;
    }
}
