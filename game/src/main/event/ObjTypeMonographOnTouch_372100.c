/* rgp:protos */
#define RGP_SELF_ObjTypeMonographOnTouch_372100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/ /* extern */
/*rgp*/ /* extern */
/*rgp*/ /* extern */
/*rgp*/ /* extern */
/*rgp*/ /* extern */
/*rgp*/ /* extern */
/*rgp*/ /* extern */
/*rgp*/ /* extern */
/*rgp*/ /* extern */
/*rgp*/ /* extern */

void ObjTypeMonographOnTouch_372100(u8 *arg0, s32 arg1) {
    s32 temp_17;
    s32 temp_2;
    s32 temp_2_2;

    temp_17 = GameSceneSoundSlot5GetHandle_1d0790(GetCurrentScene_1f5be0());
    SoundPlayScaledVolume_1b9520(temp_17, 0x50, SoundNextPlayHandle_1b81c0(), 1.0f);
    ObjTypeMonographStartTouchTimer_372a90(arg0);
    temp_2 = ((short)TargetRefGetKind_2e7130(arg0 + 0xA0));
    switch (temp_2) {
    case 4:
    case 5:
        break;
    default:
        return;
    }
    if (*(s32 *)(arg0 + 0xD0) & 0x4000) {
        temp_2_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), arg1));
        if ((temp_2_2 != 0) && (((short)CharaGetActionKind_213840(temp_2_2)) != 4) && (((short)CharaGetActionKind_213840(temp_2_2)) != 5) && (((short)CharaGetActionKind_213840(temp_2_2)) != 0x14)) {
            CharaAddFlags_212460(temp_2_2, (s64) 0x2000 << 0x20);
        }
    }
}
