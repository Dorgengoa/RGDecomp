/* rgp:protos */
#define RGP_SELF_MesWinPageCharCount_24e350 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimize_for_size on

/*rgp*/
/*rgp*/
extern void memcpy(s8 *dst, s32 src, s32 n);
extern s32 strlen(s8 *arg0);
extern s8 D_0045EC38[0x400];
extern u8 D_0045EC40[0x400];

s32 MesWinPageCharCount_24e350(s32 arg0, s32 arg1)
{
    s8 sp40[0x400] __attribute__((aligned(16)));
    s32 temp_2_4;
    s32 var_17;
    s32 var_3;
    s8 *temp_2;
    s8 *temp_2_2;
    s8 *temp_2_3;
    s8 *var_16;

    if (arg0 == 0) {
        return -1;
    }
    if (MesWinGetLabelText_274e10(arg0) == 0) {
        return -1;
    }
    memcpy(sp40, MesWinGetLabelText_274e10(arg0), 0x400);
    temp_2 = ((s8 *)Strstr_135138(sp40, D_0045EC38));
    if (temp_2 != NULL) {
        *temp_2 = 0;
    }
    var_16 = sp40;
    for (var_17 = 0; var_17 < arg1; var_17++) {
        temp_2_2 = ((s8 *)Strstr_135138(var_16, &(*(s8 *)D_0045EC40)));
        if (temp_2_2 == NULL) {
            return -1;
        }
        var_16 = temp_2_2 + strlen(&(*(s8 *)D_0045EC40));
    }
    temp_2_3 = ((s8 *)Strstr_135138(var_16, &(*(s8 *)D_0045EC40)));
    if (temp_2_3 == NULL) {
        return -1;
    }
    *temp_2_3 = 0;
    return strlen(var_16) / 2;
}
