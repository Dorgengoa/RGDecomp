#include "types.h"

s32 DrawCtxVif1HandlerStop_15dc40();
s32 SceneTableRemoveNamedData_196330(s32, s32);
s32 SceneTableRemoveModelCfg_1965c0(s32, s32);
s32 LoaderReleaseHandle_1ccb70(u8 *);
s32 ObjRecRelease_1ce9c0(s32, s16, s32);
s32 MapAreaDataReset_1e8fe0(u8 *);
s32 GetCurrentScene_1f5be0();

void MapAreaDataRelease_1e8ef0(u8 *arg0) {
    s32 h;
    s32 base;
    s32 i;
    s32 x;
    s32 j;

    if (*(s16 *)(arg0 + 0x16C8) >= 0) {
        h = GetCurrentScene_1f5be0();
        base = h + 0x4020;
        for (i = 0; (x = *(s32 *)(arg0 + i * 4 + 0x16E4)) != 0; i++) {
            SceneTableRemoveNamedData_196330(base, x);
        }
        for (i = 0; (x = *(s32 *)(arg0 + i * 4 + 0x16F4)) != 0; i++) {
            SceneTableRemoveModelCfg_1965c0(base, x);
        }
        ObjRecRelease_1ce9c0(h, *(s16 *)(arg0 + 0x16C8), 0);
    }
    for (j = 0; j < 4; j++) {
        LoaderReleaseHandle_1ccb70(arg0 + j * 0xC);
    }
    MapAreaDataReset_1e8fe0(arg0);
    DrawCtxVif1HandlerStop_15dc40();
}
