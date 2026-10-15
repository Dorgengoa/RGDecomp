#include "types.h"

s32 SoundNextPlayHandle_1b81c0(void); /* extern */
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32); /* extern */
s32 GameSceneSoundSlot5GetHandle_1d0790(s32); /* extern */
s32 GetCurrentScene_1f5be0(void); /* extern */
s32 GetActionMgr_1fdb50(void); /* extern */
void CharaAddFlags_212460(s32, s64); /* extern */
s32 CharaGetActionKind_213840(s32); /* extern */
s32 ActionMgrFindById_233b50(s32, s32); /* extern */
s32 TargetRefGetKind_2e7130(void *); /* extern */
void ObjTypeMonographStartTouchTimer_372a90(void *); /* extern */

void ObjTypeMonographOnTouch_372100(u8 *arg0, s32 arg1) {
    s32 temp_17;
    s32 temp_2;
    s32 temp_2_2;

    temp_17 = GameSceneSoundSlot5GetHandle_1d0790(GetCurrentScene_1f5be0());
    SoundPlayScaledVolume_1b9520(temp_17, 0x50, SoundNextPlayHandle_1b81c0(), 1.0f);
    ObjTypeMonographStartTouchTimer_372a90(arg0);
    temp_2 = TargetRefGetKind_2e7130(arg0 + 0xA0);
    switch (temp_2) {
    case 4:
    case 5:
        break;
    default:
        return;
    }
    if (*(s32 *)(arg0 + 0xD0) & 0x4000) {
        temp_2_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), arg1);
        if ((temp_2_2 != 0) && (CharaGetActionKind_213840(temp_2_2) != 4) && (CharaGetActionKind_213840(temp_2_2) != 5) && (CharaGetActionKind_213840(temp_2_2) != 0x14)) {
            CharaAddFlags_212460(temp_2_2, (s64) 0x2000 << 0x20);
        }
    }
}
