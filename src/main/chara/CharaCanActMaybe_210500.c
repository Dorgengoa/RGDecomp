#include "types.h"

extern s32 MapSlotsFindById_1e4b90(s32 arg0, s32 arg1, s32 arg2);
extern s32 MapDataIsJasterOnly_1e7a90(s32 arg0);
extern s32 GetMapMgr_201a90(void);

s32 CharaCanActMaybe_210500(void *arg0)
{
    s16 m;
    s32 t;

    if (!(*(s32 *)((u8 *)arg0 + 0x3D8) & 1)) {
        return 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0xA38) != 0) {
        m = *(s16 *)((u8 *)arg0 + 0xA36);
        if (m == 2) {
            return 0;
        }
        if (m == 30) {
            return 0;
        }
        if (m == 31) {
            return 0;
        }
    }
    if (*(s16 *)((u8 *)arg0 + 0xA2E) != 0) {
        return 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0xA32) != 0) {
        return 0;
    }
    t = MapSlotsFindById_1e4b90(GetMapMgr_201a90(), *(s32 *)((u8 *)arg0 + 0xA4C), 0);
    if ((t != 0) && (MapDataIsJasterOnly_1e7a90(t) != 0)) {
        return 0;
    }
    return 1;
}
