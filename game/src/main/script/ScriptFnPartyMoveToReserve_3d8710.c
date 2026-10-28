/* rgp:protos */
#define RGP_SELF_ScriptFnPartyMoveToReserve_3d8710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00483960;
extern s32 D_00483964;

void ScriptFnPartyMoveToReserve_3d8710(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *temp_2;
    s32 temp_3;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    temp_2 = CharaMgrPoolFindByDataId_3a8a70(*(s32 *)((u8 *)D_00483960 + 0x14), (int)((s64)(s16)VariantGetS16_36fcc0(arg3)), 1, 1, 0, 0, 0
);
    if (temp_2 != NULL) {
        temp_3 = *(volatile s32 *)((u8 *)temp_2 + 0xC);
        VariantSetS32_36f040(arg0,
            PartyMoveToReserve_3c19b0(*(s32 *)((u8 *)D_00483960 + 0x18), temp_3, 1, 0) != 0,
            1);
    }
}
