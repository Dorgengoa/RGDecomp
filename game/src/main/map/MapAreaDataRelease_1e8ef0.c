/* rgp:protos */
#define RGP_SELF_MapAreaDataRelease_1e8ef0 1
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
    MapAreaDataReset_1e8fe0(arg0, 0, 0, 0);
    DrawCtxVif1HandlerStop_15dc40();
}
