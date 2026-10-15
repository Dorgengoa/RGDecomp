#include "types.h"

extern s32 MinimapSlotIsActive_322510(s32);
extern char *MinimapSlotGetName_322520(s32);
extern s32 strcmp(const char *, const char *);

s32 MinimapMgrFindSlotByName_322340(s32 arg0, const char *arg1) {
    s32 temp_19;
    s32 var_16;

    if (arg1 == NULL) {
        return 0;
    }
    var_16 = 0;
    while (var_16 < 3) {
        temp_19 = arg0 + (var_16 * 0x1B0);
        if (MinimapSlotIsActive_322510(temp_19) != 0 && strcmp(MinimapSlotGetName_322520(temp_19), arg1) == 0) {
            return temp_19;
        }
        var_16 += 1;
    }
    return 0;
}
