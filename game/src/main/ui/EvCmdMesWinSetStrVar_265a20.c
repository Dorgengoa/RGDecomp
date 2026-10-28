/* rgp:protos */
#define RGP_SELF_EvCmdMesWinSetStrVar_265a20 1
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
extern void strncpy(void *dst, s32 src, s32 n);

s32 EvCmdMesWinSetStrVar_265a20(s64 *arg0)
{
        s32 arg_h1;

    s8 sp14F;
    u8 sp50[0x100] __attribute__((aligned(16)));
    s32 temp_2;
    s32 temp_18;
    s32 temp_16;
    s32 temp_2_2;
    s32 temp_2_3;
    s32 var_2;
    s8 *temp_2_4;
    s8 *temp_2_5;
    u8 *temp_17_2;
    u8 *temp_17;


    temp_2 = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(arg0++));
    if (temp_2 == 0) {
        return 0;
    }
    temp_16 = ScriptGetInt_26a2a0(arg0++);
    if (*(s32 *) (arg0) == 2) {
        var_2 = ScriptGetCodeAddr_26a200(arg0);
    } else {
        temp_18 = ScriptGetInt_26a2a0(arg0);
        temp_2_2 = MesWinGetTextFile_274e40(temp_2);
        if(temp_2_2 == 0) {
            return 0;
        } else {
            temp_2_3 = MesWinGetTextFileSize_274e30(temp_2);
            if (temp_2_3 <= 0) {
                return 0;
            } else {
                var_2 = TextFindAtLabelLine_2772f0(temp_2_2, temp_2_3, temp_18);
                if (var_2 == 0) {
                    return 0;
                }
            }
        }
    }
    strncpy(sp50, var_2, 0x100);
    sp50[255] = 0;
    arg_h1 = 0xD;
    temp_2_4 = ((s8 *)Strchr_1347c0(sp50, arg_h1));
    if (temp_2_4 != NULL) {
        *temp_2_4 = 0;
    }
    temp_2_5 = ((s8 *)Strchr_1347c0(sp50, 0xA));
    if (temp_2_5 != NULL) {
        *temp_2_5 = 0;
    }
    MesWinSetStrVar_276a00(temp_2, temp_16 - 1, sp50);
    return 1;
    return 0;
}
