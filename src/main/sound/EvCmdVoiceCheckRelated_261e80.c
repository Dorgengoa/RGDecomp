#include "types.h"

extern s32 VoiceFileCheckStubMaybe_261f30(s32, s32);
extern s32 VoicePakCheckStubMaybe_261f80(s32, s32, s32);
extern s32 ScriptGetCodeAddr_26a200(s32);
extern void ScriptGetInt_26a2a0(s32);
extern s32 D_004BDA24[0x100];

s32 EvCmdVoiceCheckRelated_261e80(s64 *arg0, s32 arg1) {
    s32 temp_16;
    s16 temp_17;

    ScriptGetInt_26a2a0((s32)arg0++);
    switch (arg1) {
        case 2:
            D_004BDA24[0] = 0;
            return VoiceFileCheckStubMaybe_261f30(1, ScriptGetCodeAddr_26a200((s32)arg0));
        case 3:
            D_004BDA24[0] = 1;
            temp_16 = ScriptGetCodeAddr_26a200((s32)arg0++);
            return VoicePakCheckStubMaybe_261f80(1, temp_16, ScriptGetCodeAddr_26a200((s32)arg0));
        default:
            return 0;
    }
}
