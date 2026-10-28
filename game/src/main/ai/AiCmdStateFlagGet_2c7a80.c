/* rgp:protos */
#define RGP_SELF_AiCmdStateFlagGet_2c7a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdStateFlagGet_2c7a80(s64 *arg0)
{
    s64 *p;
    s32 kind;
    u8 r;
    void *ctx;

    p = arg0;
    ctx = GetGameData_1fede0();
    kind = *(s32 *)p;
    r = 0;
    switch (kind) {
    case 0:
    case 1:
        r = StateFlagTest_3ccd70(*(s32 *)((u8 *)ctx + 0x10), ScriptSlotGetInt_2cc9c0(p++));
        break;
    case 2:
        r = StateFlagTestByName_3ccd10(*(s32 *)((u8 *)ctx + 0x10), ScriptSlotGetCodeAddr_2cc980(p++));
        break;
    }
    ScriptSlotStoreIntRef_2cc900(p, r);
    return 1;
}
