#include "types.h"

extern s32 MapSlotsFindActiveById_1e4870(s32, s16, s32);
extern s32 MapDataIsLoaded_1e79d0(s32);
extern s32 GetMapMgr_201a90(void);
extern s32 TargetRefGetKind_2e7130(void *);

s32 TargetRefIsActive_2e6f00(void *arg0)
{
    s32 t;

    switch (TargetRefGetKind_2e7130(arg0)) {
    case 1:
    case 13:
        return 1;
    }
    if (*(s32 *)((u8 *)arg0 + 4) == 0) {
        return 0;
    }
    t = TargetRefGetKind_2e7130(arg0);
    if (t != 9 && t != 8 && t != 7 && t != 6) {
        return 1;
    }
    t = MapSlotsFindActiveById_1e4870(GetMapMgr_201a90(), *(s16 *)((u8 *)arg0 + 2), 0);
    if (t == 0) goto out0;
    return MapDataIsLoaded_1e79d0(t);
out0:
    return 0;
}
