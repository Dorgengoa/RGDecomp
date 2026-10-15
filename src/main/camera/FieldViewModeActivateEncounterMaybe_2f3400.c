#include "types.h"

extern void MemStackHeapReinit_14de90(s32);
extern s32 GetInsectCageMgr_1fdb30(void);
extern s32 GetNpcDataHeap_1fdd70(void);
extern void *GetGameData_1fede0(void);
extern void FieldResetNpcDataStack_2f3560(s32);
extern void FieldViewModeSet_2f3590(s32);
extern s32 FieldViewModeGet_2f35a0(void);
extern void FieldViewModeLeave_2f3660(s32, s32);
extern void InsectCageMgrReleaseAll_39a2e0(s32);
extern s32 CharaSysStateFlag24Bit2Related_3a3880(void *);

void FieldViewModeActivateEncounterMaybe_2f3400(void) {
    s16 temp_2;
    s32 temp_2_2;
    s32 var_4;
    void *temp_3;
    void *temp_4;
    void *var_16;

    if (FieldViewModeGet_2f35a0() == 2) {
        return;
    }
    temp_4 = *(void **)((u8 *)GetGameData_1fede0() + 0x20);
    temp_3 = *(void **)((u8 *)temp_4 + 0x238);
    if (temp_3 != NULL) {
        var_16 = *(void **)((u8 *)temp_3 + 0x18);
    } else {
        var_16 = NULL;
    }
    if (var_16 == NULL) {
        return;
    }
    if (CharaSysStateFlag24Bit2Related_3a3880(temp_4) != 0) {
        if (FieldViewModeGet_2f35a0() != 0) return;
        {
            InsectCageMgrReleaseAll_39a2e0(GetInsectCageMgr_1fdb30());
            FieldViewModeLeave_2f3660(0xFFFF, 1);
            MemStackHeapReinit_14de90(GetNpcDataHeap_1fdd70());

        }
    } else {
        FieldResetNpcDataStack_2f3560((*(s16 *)((u8 *)var_16 + 0x1E) << 10) / 16);
    }
    FieldViewModeSet_2f3590(2);
}
