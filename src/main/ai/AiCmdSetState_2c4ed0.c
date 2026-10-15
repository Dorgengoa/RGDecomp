#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 ScriptSlotGetInt_2cc9c0(E8 *);
extern void AiSetState_2bbc40(s32, s32);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetAi_214a10(s32);

extern const s32 D_004DB930;

s32 AiCmdSetState_2c4ed0(E8 *p0, s32 p1)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;

    t0 = D_004DB930;
    if (t0 == 0) {
        return 0;
    }
    if (p1 == 1) {
        r0 = ScriptSlotGetInt_2cc9c0(p0++);
        t1 = *(volatile s32 *)&D_004DB930;
        AiSetState_2bbc40(t1, r0);
    }
    if (p1 == 2) {
        r3 = ScriptSlotGetInt_2cc9c0(p0++);
        r4 = ScriptSlotGetInt_2cc9c0(p0);
        r5 = GetActionMgr_1fdb50();
        r6 = ActionMgrFindById_233b50(r5, r3);
        if (r6 == 0) {
            return 0;
        }
        r7 = CharaGetAi_214a10(r6);
        if (r7 == 0) {
            return 0;
        }
        AiSetState_2bbc40(r7, r4);
    }
    return 1;
}
