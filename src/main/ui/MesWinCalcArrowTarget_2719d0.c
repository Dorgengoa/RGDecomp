/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: length-wrong (75w vs retail 85w), large gap. */
#include "types.h"
#pragma opt_propagation off

s32 FontGetLineHeight_26f3e0(void *);
s32 MesWinGetChoiceIndex_271b50(void);
s32 MesWinSumLineHeights_272250(void *, s32);
s32 MesWinGetLineWidth_272350(void *, s32);
extern s32 D_0045F200[0x100];

void MesWinCalcArrowTarget_2719d0(u8 *arg0) {
    s32 temp_16;
    s32 temp_2;
    s32 temp_3_2;
    s32 var_16;
    s32 var_18;
    s32 var_19;
    s32 var_18_2;
    s32 var_2;
    s32 var_4;
    s64 temp_3;

    if (MesWinGetChoiceIndex_271b50() >= 0) {
        *(s32 *)(arg0 + 0x1C28) = (*(s32 *)(arg0 + 0x40) - 0x22) - ((s16)(D_0045F200[0] - 1)) / 2;
        temp_16 = FontGetLineHeight_26f3e0(arg0) & 0xFF;
        *(s32 *)(arg0 + 0x1C2C) = (((u32) (temp_16 & 0xFF) >> 1) + (*(s32 *)(arg0 + 0x1C44) + (*(s32 *)(arg0 + 0x44) + MesWinSumLineHeights_272250(arg0, *(s32 *)(arg0 + 0x1C24))))) - 0xA;
        if ((*(s8 *)(arg0 + 0x1DED) != 0) && (*(s8 *)(arg0 + 0x1C3A) != 0)) {
            var_16 = 0;
            var_18 = 0;
            while (var_18 < 0x14) {
                if (MesWinGetLineWidth_272350(arg0, var_18) >= 0) {
                    var_16 += 1;
                    var_18 += 1;
                    continue;
                }
                break;
            }
            var_18_2 = *(s32 *)(arg0 + 0x1C40);
            var_19 = 0;
            while (var_18_2 < var_16) {
                temp_2 = MesWinGetLineWidth_272350(arg0, var_18_2);
                if (var_19 < temp_2) {
                    var_19 = temp_2;
                }
                var_18_2 += 1;
            }
            temp_3_2 = *(s16 *)(arg0 + 0x54) - var_19;
            var_4 = temp_3_2 >> 1;
            if (temp_3_2 < 0) {
                var_4 = (s32) (temp_3_2 + 1) >> 1;
            }
            *(s32 *)(arg0 + 0x1C28) = *(s32 *)(arg0 + 0x1C28) + var_4;
        }
    }
}
