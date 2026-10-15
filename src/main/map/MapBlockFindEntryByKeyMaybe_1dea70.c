#include "types.h"

extern s16 *MapEntryGetRec_1e1240(s32);
extern s32 MapDataIsLoadedOrUnloading_1e7980(void);

s32 MapBlockFindEntryByKeyMaybe_1dea70(void *arg0, s32 arg1) {
    s16 *temp_2;
    s32 var_17;
    s32 var_16;

    if (MapDataIsLoadedOrUnloading_1e7980() == 0) {
        return 0;
    }
    var_17 = *(s32 *)((u8 *)arg0 + 0xC0);
    if (var_17 == 0) {
        return 0;
    }
    for (var_16 = 0; var_16 < *(s16 *)((u8 *)arg0 + 0xC8); var_16++, var_17 += 0x7A0) {
        temp_2 = MapEntryGetRec_1e1240(var_17);
        if (temp_2 != NULL && *temp_2 == arg1) {
            return var_17;
        }
    }
    return 0;
}
