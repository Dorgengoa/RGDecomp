#include "types.h"

struct S8 { s32 a; s32 b; };

extern s32 ScriptGetInt_26a2a0(struct S8 *);
extern s32 ScriptGetCodeAddr_26a200(struct S8 *);
extern void VoiceFileCheckStubMaybe_2618c0(s32, s32);

extern const s32 D_004BDA24;

void EvCmdVoiceFileCheckRelated_261870(struct S8 *p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_26a2a0(p0++);
    *(s32 *)&D_004BDA24 = 0;
    r1 = ScriptGetCodeAddr_26a200(p0);
    VoiceFileCheckStubMaybe_2618c0(1, r1);
}
