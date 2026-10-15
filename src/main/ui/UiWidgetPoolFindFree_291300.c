#pragma divbyzerocheck on
#pragma optimization_level 3
#include "types.h"

typedef struct Elem {
    s32 unk0;
    u8 pad4[8];
} Elem;

typedef struct S00291300 {
    Elem *unk0;
    u8 pad4[0xA];
    s16 unkE;
} S00291300;

Elem *UiWidgetPoolFindFree_291300(S00291300 *arg0, Elem *arg1) {
    Elem *var_5;
    s32 var_6;

    var_6 = 0;
    var_5 = arg1;
    if (var_5 == NULL) {
        var_5 = arg0->unk0;
        var_6 = (u32)(var_5 - arg0->unk0) / 4;
    }
    while (var_6 < arg0->unkE) {
        if (var_5->unk0 == 0) {
            return var_5;
        }
        var_5 += 1;
        var_6 += 1;
    }
    return NULL;
}
