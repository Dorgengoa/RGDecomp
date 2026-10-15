#include "types.h"
#pragma opt_common_subs off
extern void *GetGameData_1fede0(void);
extern void FieldViewModeActivateEncounterMaybe_2f3400(void);
extern void FieldViewModeActivateMaybe_2f34d0(void);
extern void FieldViewModeReset_2f3510(void);
extern s32 CharaSysStateField28ValidRelated_3a3920(void *arg0);

s32 EvCmdFieldViewModeRefreshMaybe_260460(void) {
    void *t2;
    void *t4;
    void *t16;

    t2 = GetGameData_1fede0();
    t4 = *(void **)((u8 *)t2 + 0x20);
    t16 = *(void **)((u8 *)t4 + 0x238);
    if (t16 == NULL) {
        return 0;
    }
    if (CharaSysStateField28ValidRelated_3a3920(t4) != 0) {
        if (*(s32 *)((u8 *)t16 + 0x18) != 0) {
            FieldViewModeActivateEncounterMaybe_2f3400();
            return 1;
        }
    } else if ((*(u8 *)((u8 *)(*(void **)((u8 *)t2 + 0x20)) + 0x24C) & 1) && *(s32 *)((u8 *)t16 + 0x10) != 0) {
        FieldViewModeActivateMaybe_2f34d0();
        return 1;
    }
    FieldViewModeReset_2f3510();
    return 1;
}
