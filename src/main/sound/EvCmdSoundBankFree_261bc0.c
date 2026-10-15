#include "types.h"

/* Known-positive sibling shape of EvCmdEventObjMgrResolveAndResetAll_2403f0 (byte-identical, in cunits). */

extern s32 ScriptGetInt_26a2a0(void);
extern s32 SoundBankFree_1b9c00(s32);

s32 EvCmdSoundBankFree_261bc0(void)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_26a2a0();
    r1 = SoundBankFree_1b9c00(r0);
    return 1;
}
