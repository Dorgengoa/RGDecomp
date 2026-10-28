/* rgp:protos */
#define RGP_SELF_AiCmdCharaPickFrontTargetMaybe_2cb340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S8 { s32 a; s32 b; };

/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdCharaPickFrontTargetMaybe_2cb340(struct S8 *p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptSlotGetInt_2cc9c0(p0++);
    r1 = CharaPickFrontTargetMaybe_2d0970(r0);
    ScriptSlotStoreIntRef_2cc900(p0, r1);
    return 1;
}
