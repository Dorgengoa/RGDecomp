/* rgp:protos */
#define RGP_SELF_AiCmdStrIntern_2c1ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
extern u32 strlen(const char *s);
extern s32 D_004825DC;

s32 AiCmdStrIntern_2c1ac0(s32 arg0, s32 arg1)
{ __typeof__(arg0) rgp_entry_arg0 = arg0;
    s32 s;

    if (D_004825DC == 0) {
        ScriptSlotStoreIntRef_2cc900(arg0, -1);
        return 0;
    }
    if (arg1 != 2) {
        ScriptSlotStoreIntRef_2cc900(arg0, -1);
        return 1;
    }
    arg0 += 8;
    s = ScriptSlotGetCodeAddr_2cc980((void *)rgp_entry_arg0);
    if (strlen((const char *)s) >= 0x50) {
        ScriptSlotStoreIntRef_2cc900(arg0, -1);
        return 0;
    }
    ScriptSlotStoreIntRef_2cc900(arg0, ScriptStrTableIntern_2cce20(s));
    return 1;
}
