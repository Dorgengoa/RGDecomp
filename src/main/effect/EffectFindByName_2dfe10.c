#include "types.h"

extern s32 EffectEntryGetName_2d9540(void *arg0);
extern s32 NameHash16_2e3470(s32 arg0);
extern s32 strcmp(s32 arg0, s32 arg1);

typedef struct {
    u8 pad00[0xDC];
    u16 unkDC;
    u8 pad00DE[0x2];
} Elem002DFE10;

Elem002DFE10 *EffectFindByName_2dfe10(Elem002DFE10 *arg0, s32 arg1, s16 *arg2)
{
    s32 var_18;
    s32 temp_16;
    Elem002DFE10 *temp_17;

    temp_16 = NameHash16_2e3470(arg1) & 0xFFFF;
    var_18 = 0;
    while (var_18 < 0x30) {
        temp_17 = &arg0[var_18];
        if (temp_16 == temp_17->unkDC && strcmp(arg1, EffectEntryGetName_2d9540(temp_17)) == 0) {
            *arg2 = var_18;
            return temp_17;
        }
        var_18 += 1;
    }
    return NULL;
}
