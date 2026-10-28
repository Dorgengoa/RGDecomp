/* rgp:protos */
#define RGP_SELF_MenuTestStep_203ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                                /* extern */
/*rgp*/                                /* extern */
/*rgp*/                             /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                           /* extern */
/*rgp*/                /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
s32 strcmp(s32, s32);                               /* extern */
extern u8 D_0044B770[0x400];
extern s32 D_00481BE4;
extern s32 D_00481C54;
extern u8 D_004B27E0[0x400];
extern u8 D_004BBE00[0x400];

void MenuTestStep_203ac0(void) {
    s32 *temp_16;
    s32 temp_20;
    s32 var_19;
    u16 var_18;
    s32 var_17;

    temp_16 = (s32 *)((u8 *)&(*(s32 *)D_0044B770) + (D_00481C54 * 0xC));
    var_18 = 0;
    var_17 = 0;
    var_19 = 0;
    temp_20 = *temp_16;
    if (PadIsTriggered_1839f0(&(*(s32 *)D_004B27E0), 0x2000) != 0) {
        var_17++;
    } else {
        if ((PadIsTriggered_1839f0(&(*(s32 *)D_004B27E0), 0x8000) != 0) && (D_00481C54 > 0)) {
            var_17--;
        }
    }
    if (var_17 != 0) {
        var_19 = *(s32 *)((u8 *)temp_16 + (var_17 * 0xC));
        if (var_19 != 0) {
            var_18 = 1;
            D_00481C54 += var_17;
        }
    }
    if ((var_18) && (strcmp(temp_20, var_19) != 0)) {
        MenuTestStackRelease_206530();
        MemStackClear_14dff0(&(*(s32 *)D_004BBE00));
        D_00481BE4 = -1;
        MenuTestStackInit_206540();
        MemStackReset_14d830(&(*(s32 *)D_004BBE00));
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32F);
        TexGroupLoadFromResident_202c80(var_19, &(*(s32 *)D_004BBE00), 0x32F, &(*(s32 *)D_004BBE00), 0);
    }
}
