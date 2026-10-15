#include "types.h"
#pragma opt_common_subs off

extern s32 GameReqQueueContainsId_1f5b90(s32);
extern s32 GetActionMgr_1fdb50(void);
extern s32 CharaIsControllableMaybe_20ff00(s32);
extern s32 CharaEvObjContactFlag2Related_2148e0(s32);
extern s32 CharaEvObjContactFlag1Related_214920(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 IsInBattle_288420(void);

s32 CharaGetControlStateMaybe_2f5320(s32 arg0)
{
    s32 temp_2;

    if ((IsInBattle_288420() != 0) && (*(s16 *)0x5273C2 == 4)) {
        return 1;
    }
    if (!(GameReqQueueContainsId_1f5b90(0xB) == 0)) {
        return 1;
    }
    if (GameReqQueueContainsId_1f5b90(7) != 0) {
        return 1;
    }
    if (GameReqQueueContainsId_1f5b90(9) != 0) {
        return 1;
    }
    if (GameReqQueueContainsId_1f5b90(0xA) != 0) {
        return 1;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), arg0);
    if (temp_2 == 0) goto r0;
    if (CharaEvObjContactFlag1Related_214920(temp_2) != 0) {
        return 2;
    }
    if (CharaEvObjContactFlag2Related_2148e0(temp_2) != 0) {
        return 2;
    }
    if (CharaIsControllableMaybe_20ff00(temp_2) != 0) goto r0;
    return 3;
r0:
    return 0;
}
