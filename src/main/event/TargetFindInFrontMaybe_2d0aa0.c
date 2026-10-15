#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindTargetInFrontMaybe_2330f0(s32, s32, s32, f32, f32);
extern s32 GetEventObjMgr_2d1960(void);
extern void TargetRefClear_2e71d0(void);
extern s32 EvMapObjFindTargetInFrontMaybe_2e9560(s32, s32, s32, f32, f32);

s32 TargetFindInFrontMaybe_2d0aa0(s32 arg0, s32 arg1, f32 fparg0, f32 fparg1)
{
    s32 temp_2;

    if (arg0 == 0) {
        return -1;
    }
    TargetRefClear_2e71d0();
    temp_2 = ActionMgrFindTargetInFrontMaybe_2330f0(GetActionMgr_1fdb50(), arg0, arg1, fparg0, fparg1);
    if (temp_2 != -1) {
        return temp_2;
    }
    if (EvMapObjFindTargetInFrontMaybe_2e9560(GetEventObjMgr_2d1960(), arg0, arg1, fparg0, fparg1) != 0) {
        return 1;
    }
    return -1;
}
