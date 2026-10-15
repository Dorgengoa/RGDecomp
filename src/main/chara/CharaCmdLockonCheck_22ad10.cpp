#include "types.h"

extern "C" {
extern s32 GetGameData_1fede0(void);
extern s32 CharaCmdRunIfElseEvnt_22e480(s32, bool, s32, s32);
extern s32 TargetMngHasTargetId_313bf0(void);
}
extern "C" s32 CharaCmdLockonCheck_22ad10(s32 *arg0, s32 arg1, s32 arg2) {
    bool f;
    s32 v;
    switch (arg2) {
    case 2:
    case 1:
        break;
    default:
        return 1;
    }
    v = *(s16 *)((u8 *)(*(void **)((u8 *)GetGameData_1fede0() + 0x18)) + 0x18E);
    f = false;
    if (*arg0 != v) {
        goto call;
    }
    if (TargetMngHasTargetId_313bf0() != 0) {
        f = true;
    }
call:
    return CharaCmdRunIfElseEvnt_22e480(*arg0, f, arg1, arg2);

}
