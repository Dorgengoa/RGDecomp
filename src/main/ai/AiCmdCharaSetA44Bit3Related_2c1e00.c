#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern u8 *ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern s32 ScriptSlotGetInt_2cc9c0();
extern u8 *D_004DB92C __attribute__((section(".data")));

s32 AiCmdCharaSetA44Bit3Related_2c1e00(s64 *arg0, s32 arg1)
{
    s32 a;
    s32 b;
    u8 *p;
    s32 v;

    if (arg1 == 1) {
        a = ScriptSlotGetInt_2cc9c0(arg0);
        p = D_004DB92C;
        if (p != NULL) {
            if (a != 0) {
                v = *(s32 *)(p + 0xA44) | 8;
            } else {
                v = *(s32 *)(p + 0xA44) & ~8;
            }
            *(s32 *)(p + 0xA44) = v;
        }
    } else if (arg1 == 2) {
        a = ScriptSlotGetInt_2cc9c0((s32)arg0++);
        b = ScriptSlotGetInt_2cc9c0(arg0);
        p = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), a);
        if (p != NULL) {
            if (b != 0) {
                v = *(s32 *)(p + 0xA44) | 8;
            } else {
                v = *(s32 *)(p + 0xA44) & ~8;
            }
            *(s32 *)(p + 0xA44) = v;
        }
    }
    return 1;
}
