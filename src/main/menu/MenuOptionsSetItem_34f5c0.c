#include "types.h"

extern s32 GetGameData_1fede0(void);
extern void OptionsApply_1fe350(void);
extern void MenuOptionsChoiceHighlight_34fa80(s32, s32);
extern void OptionsSetCameraBitMaybe_3d6080(s32, s32);
extern void OptionsSetFlagMaybe_3d5fe0(s32, s32);
extern void OptionsSetSoundOutput_3d6160(s32, s32);
extern void OptionsSetCursorMemory_3d5fc0(s32, s32);
extern void OptionsSetCompassShown_3d5f80(s32, s32);
extern void OptionsSetMinimapShown_3d5fa0(s32, s32);
extern void OptionsSetCameraInvertY_3d6060(s32, s32);
extern void OptionsSetCameraInvertX_3d6040(s32, s32);
extern void OptionsSetEventLogEnabled_3d5f60(s32, s32);
extern void OptionsSetFlagMaybe_3d6000(s32, s32);

s32 MenuOptionsSetItem_34f5c0(s32 arg0, s32 arg1) {
    s32 obj;

    obj = GetGameData_1fede0();
    if (arg1 == 0) {
        if (arg0 == 0) {
            OptionsSetCameraBitMaybe_3d6080(*(s32 *)(obj + 0xC), 1);
            MenuOptionsChoiceHighlight_34fa80(0x1B7, 0x1B8);
        } else {
            OptionsSetCameraBitMaybe_3d6080(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1B8, 0x1B7);
        }
    } else if (arg1 == 1) {
        if (arg0 == 0) {
            OptionsSetFlagMaybe_3d5fe0(*(s32 *)(obj + 0xC), 1);
            MenuOptionsChoiceHighlight_34fa80(0x1B9, 0x1BA);
        } else {
            OptionsSetFlagMaybe_3d5fe0(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1BA, 0x1B9);
        }
    } else if (arg1 == 2) {
        if (arg0 == 0) {
            OptionsSetSoundOutput_3d6160(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1BB, 0x1BC);
        } else {
            OptionsSetSoundOutput_3d6160(*(s32 *)(obj + 0xC), 1);
            MenuOptionsChoiceHighlight_34fa80(0x1BC, 0x1BB);
        }
    } else if (arg1 == 3) {
        if (arg0 == 0) {
            OptionsSetCursorMemory_3d5fc0(*(s32 *)(obj + 0xC), 1);
            MenuOptionsChoiceHighlight_34fa80(0x1BD, 0x1BE);
        } else {
            OptionsSetCursorMemory_3d5fc0(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1BE, 0x1BD);
        }
    } else if (arg1 == 4) {
        if (arg0 == 0) {
            OptionsSetCompassShown_3d5f80(*(s32 *)(obj + 0xC), 1);
            MenuOptionsChoiceHighlight_34fa80(0x1BF, 0x1C0);
        } else {
            OptionsSetCompassShown_3d5f80(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1C0, 0x1BF);
        }
    } else if (arg1 == 5) {
        if (arg0 == 0) {
            OptionsSetMinimapShown_3d5fa0(*(s32 *)(obj + 0xC), 1);
            MenuOptionsChoiceHighlight_34fa80(0x1C1, 0x1C2);
        } else {
            OptionsSetMinimapShown_3d5fa0(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1C2, 0x1C1);
        }
    } else if (arg1 == 6) {
        if (arg0 == 0) {
            OptionsSetCameraInvertY_3d6060(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1C3, 0x1C4);
        } else {
            OptionsSetCameraInvertY_3d6060(*(s32 *)(obj + 0xC), 2);
            MenuOptionsChoiceHighlight_34fa80(0x1C4, 0x1C3);
        }
    } else if (arg1 == 7) {
        if (arg0 == 0) {
            OptionsSetCameraInvertX_3d6040(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1C5, 0x1C6);
        } else {
            OptionsSetCameraInvertX_3d6040(*(s32 *)(obj + 0xC), 4);
            MenuOptionsChoiceHighlight_34fa80(0x1C6, 0x1C5);
        }
    } else if (arg1 == 8) {
        if (arg0 == 0) {
            OptionsSetEventLogEnabled_3d5f60(*(s32 *)(obj + 0xC), 1);
            MenuOptionsChoiceHighlight_34fa80(0x1C7, 0x1C8);
        } else {
            OptionsSetEventLogEnabled_3d5f60(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1C8, 0x1C7);
        }
    } else if (arg1 == 9) {
        if (arg0 == 0) {
            OptionsSetFlagMaybe_3d6000(*(s32 *)(obj + 0xC), 1);
            MenuOptionsChoiceHighlight_34fa80(0x1C9, 0x1CA);
        } else {
            OptionsSetFlagMaybe_3d6000(*(s32 *)(obj + 0xC), 0);
            MenuOptionsChoiceHighlight_34fa80(0x1CA, 0x1C9);
        }
    }
    OptionsApply_1fe350();
    return 1;
}
