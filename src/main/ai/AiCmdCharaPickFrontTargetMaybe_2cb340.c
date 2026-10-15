#include "types.h"

struct S8 { s32 a; s32 b; };

extern s32 ScriptSlotGetInt_2cc9c0(struct S8 *);
extern s32 CharaPickFrontTargetMaybe_2d0970(s32);
extern s32 ScriptSlotStoreIntRef_2cc900(struct S8 *, s32);

s32 AiCmdCharaPickFrontTargetMaybe_2cb340(struct S8 *p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptSlotGetInt_2cc9c0(p0++);
    r1 = CharaPickFrontTargetMaybe_2d0970(r0);
    ScriptSlotStoreIntRef_2cc900(p0, r1);
    return 1;
}
