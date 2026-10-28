/* rgp:protos */
#define RGP_SELF_FieldViewModeActivateEncounterMaybe_2f3400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
            InsectCageMgrReleaseAll_39a2e0(((s32)GetInsectCageMgr_1fdb30()));
            FieldViewModeLeave_2f3660(0xFFFF, 1);
            MemStackHeapReinit_14de90(((s32)GetNpcDataHeap_1fdd70()));

        }
    } else {
        FieldResetNpcDataStack_2f3560((*(s16 *)((u8 *)var_16 + 0x1E) << 10) / 16);
    }
    FieldViewModeSet_2f3590(2);
}
