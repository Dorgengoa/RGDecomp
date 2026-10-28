/* rgp:protos */
#define RGP_SELF_EvCmdRecordAdvanceState_25f440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdRecordAdvanceState_25f440(s32 arg0, s32 arg1) {
    s32 val;
    s32 flag;
    void *ctxPtr;
    void *sub;

    ctxPtr = *(void **)((u8 *)GetGameData_1fede0() + 0x24);
    sub = *(void **)((u8 *)ctxPtr + 0x1188);
    val = *(s32 *)((u8 *)sub + 8);
    flag = RecordAdvanceState_430bf0(ctxPtr, 0) != 0;
    if (arg1 > 0) {
        s32 old = arg0;
        arg0 += 8;
        ScriptSetRefInt_26a1e0(old, flag);
    }
    if (arg1 >= 2) {
        ScriptSetRefInt_26a1e0(arg0, val);
    }
    return 1;
}
