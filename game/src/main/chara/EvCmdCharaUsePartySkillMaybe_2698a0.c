/* rgp:protos */
#define RGP_SELF_EvCmdCharaUsePartySkillMaybe_2698a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_002698a0 {
    s32 a;
    s32 b;
} E8_FUN_002698a0;

/*rgp*/
/*rgp*/

s32 EvCmdCharaUsePartySkillMaybe_2698a0(E8_FUN_002698a0 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_26a2a0(q++);
    b = ScriptGetInt_26a2a0(q);
    CharaUsePartySkillMaybe_3e08b0(a, b);
    return 1;
}
