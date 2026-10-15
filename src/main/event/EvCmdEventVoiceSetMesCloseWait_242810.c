#include "types.h"

struct EC242810 { u8 pad000[0x4]; u8 *f4; };

extern struct EC242810 *gEventContext;
extern s32 ScriptGetInt_2490f0(s32);

s32 EvCmdEventVoiceSetMesCloseWait_242810(s32 a0)
{
    u8 *b;

    b = gEventContext->f4 + 0x420;
    *(s32 *)(b + 0x10) = ScriptGetInt_2490f0(a0);
    return 1;
}
