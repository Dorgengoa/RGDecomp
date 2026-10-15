#include "types.h"

extern s32 strcmp(const s8 *, const s8 *);
extern s8 *strcpy(s8 *, const s8 *);
extern s8 **D_004825DC;
extern s32 D_004825E0;

s32 ScriptStrTableIntern_2cce20(s8 *arg0)
{
    s32 temp_2;
    s32 var_16;

    if (D_004825DC == NULL) {
        return -1;
    }
    if (D_004825E0 >= 8) {
        return -1;
    }
    var_16 = 0;
    while (var_16 < D_004825E0) {
        if (strcmp(D_004825DC[var_16], arg0) == 0) {
            return var_16;
        }
        var_16 += 1;
    }
    strcpy(D_004825DC[D_004825E0], arg0);
    temp_2 = D_004825E0 + 1;
    D_004825E0 = temp_2;
    return temp_2 - 1;
}
