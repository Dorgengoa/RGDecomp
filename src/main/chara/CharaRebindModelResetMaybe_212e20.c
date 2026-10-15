#include "types.h"

s32 ObjRecGetLiveObject_1c4a90(s32, s16);
s32 CharaResSptLoadDoneMaybe_1f08f0(s32, s16);
s32 GetCurrentScene_1f5be0();
s32 GetCharaResMgr_1fdb60();
void CharaReleaseHeldTarget_2116b0(u8 *, f32, f32, f32, s32);
void CharaSetModelObj_238700(u8 *, s32);

void CharaRebindModelResetMaybe_212e20(u8 *arg0) {
    CharaSetModelObj_238700(arg0, ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), *(s16 *)(arg0 + 0x424)));
    if (CharaResSptLoadDoneMaybe_1f08f0(GetCharaResMgr_1fdb60(), *(s16 *)(arg0 + 0x424)) == 0) {
        *(s16 *)(arg0 + 0xA2E) = 0;
        *(s16 *)(arg0 + 0xB50) = 0;
    }
    CharaReleaseHeldTarget_2116b0(arg0, 0.0f, 0.0f, 0.0f, 0);
    *(s64 *)(arg0 + 0x568) = 0;
    *(s64 *)(arg0 + 0x570) = 0;
    if (*(s16 *)(arg0 + 0xA38) == 0) {
        switch (*(s16 *)(arg0 + 0xA32)) {
        case 0:
        case 1:
        case 2:
        case 3:
            switch (*(s16 *)(arg0 + 0xA34)) {
            case 0:
            case 2:
            case 1:
                *(s16 *)(arg0 + 0xA34) = -1;
                break;
            }
            break;
        }
    }
}
