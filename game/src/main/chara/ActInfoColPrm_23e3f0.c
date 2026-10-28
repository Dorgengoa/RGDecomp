/* rgp:protos */
#define RGP_SELF_ActInfoColPrm_23e3f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                               /* extern */
/*rgp*/                           /* extern */
/*rgp*/                      /* extern */
/*rgp*/                           /* extern */
/*rgp*/                           /* extern */
/*rgp*/                              /* extern */
/*rgp*/                        /* extern */
extern u8 D_004BCE20[0x3C];
extern s32 D_004BCE5C[0xB];
extern s16 D_004BCE8A[0x8];

s32 ActInfoColPrm_23e3f0(u8 *arg0, s32 arg1) {
    s32 temp_16;
    s16 *temp_2;
    s32 var_18;
    s32 temp_18;

    if (arg1 != 2) {
        return 0;
    }
    if (D_004BCE5C[0] == 0 || D_004BCE8A[0] >= 0x20) {
        return 1;
    }
    temp_16 = D_004BCE5C[0] + (D_004BCE8A[0] * 8);
    if (*(s32 *)(arg0 + 0x8) == 0) {
        temp_18 = ScriptArgGetStr_23fba0(arg0 + 8);
        temp_2 = ((s16 *)TableFindByNameHashed_3f8180(*(s32 *)((u8 *)(*(s32 *)((u8 *)(*(s32 *)((u8 *)((u8 *)GetGameData_1fede0()) + 0x8)) + 0x50)) + 0xC), temp_18));
        if (temp_2 == 0) {
            return 1;
        }
        var_18 = *temp_2;
    } else {
        var_18 = ScriptArgGetInt_23fc00(arg0 + 8);
    }
    ActInfoColPrmInit_230920(temp_16, ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0))), var_18);
    ActCfgTableSetColPrmCount_223c30(D_004BCE20, D_004BCE8A[0] + 1);
    return 1;
}
