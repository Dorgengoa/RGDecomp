/* rgp:protos */
#define RGP_SELF_SceneCameraApplyAspect_1c6a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void SceneCameraApplyAspect_1c6a10(void *arg0) {
    s32 t16;

    if (arg0 != 0 && ((s32)ObjRecGetLiveObject_1c3bc0((s32)arg0, *(s32 *)((u8 *)arg0 + 0x4344))) != 0) {
        t16 = GetDrawCtx_15de80();
        switch (GetAspectMode_1c6aa0()) {
        case 1:
            ViewSetAspect_142f50(t16, 0.5625f);
            return;
        }
        ViewSetAspect_142f50(t16, 0.75f);
        SetAspectMode_1c6a90(0);
    }
}
