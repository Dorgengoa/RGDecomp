/* rgp:protos */
#define RGP_SELF_EvCmdMenuThinkSetPrompt_25fa10 1
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
extern void memcpy(void *dst, s32 src, s32 n);
extern s32 strlen(void *arg0);

s32 EvCmdMenuThinkSetPrompt_25fa10(s64 *arg0, s32 arg1)
{
    u8 spB0[0x20] __attribute__((aligned(16)));
    u8 sp30[0x80] __attribute__((aligned(16)));
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;
    s32 temp_3;
    u8 *var_2;

    temp_3 = *(s32 *)arg0;
    if (temp_3 == 2) {
        func_520800(ScriptGetCodeAddr_26a200((void *)arg0));
    } else if ((temp_3 == 0) && (arg1 == 2)) {
        temp_2 = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0((s32)arg0++));
        if (temp_2 != 0) {
            temp_2_2 = MesWinGetTextFile_274e40(temp_2);
            if (temp_2_2 != 0) {
                IntToDecStr_1d7d10(ScriptGetInt_26a2a0((s32)arg0), spB0);
                temp_2_3 = ((s32)Strstr_135138(temp_2_2, spB0));
                if (temp_2_3 != 0) {
                    memcpy(sp30, temp_2_3 + strlen(spB0), 0x80);
                    sp30[0x7F] = 0;
                    var_2 = Strchr_1347c0(sp30, 0x40);
                    if (var_2 == NULL) {
                        var_2 = Strchr_1347c0(sp30, 0);
                    }
                    if (var_2 != NULL) {
                        *(var_2 - 1) = 0;
                        func_520800(sp30);
                    }
                }
            }
        }
    }
    return 1;
}
