#include "types.h"

typedef struct E8_FUN_002698a0 {
    s32 a;
    s32 b;
} E8_FUN_002698a0;

extern void *ScriptGetInt_26a2a0(E8_FUN_002698a0 *p);
extern void CharaUsePartySkillMaybe_3e08b0(void *a, void *b);

s32 EvCmdCharaUsePartySkillMaybe_2698a0(E8_FUN_002698a0 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_26a2a0(q++);
    b = ScriptGetInt_26a2a0(q);
    CharaUsePartySkillMaybe_3e08b0(a, b);
    return 1;
}
