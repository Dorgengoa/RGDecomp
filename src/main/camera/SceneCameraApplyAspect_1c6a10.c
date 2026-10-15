#include "types.h"

extern s32 ObjRecGetLiveObject_1c3bc0(s32 xa0, s32);
extern s32 GetDrawCtx_15de80(void);
extern s32 GetAspectMode_1c6aa0(void);
extern void ViewSetAspect_142f50(s32, f32);
extern void SetAspectMode_1c6a90(s32);

void SceneCameraApplyAspect_1c6a10(void *arg0) {
    s32 t16;

    if (arg0 != 0 && ObjRecGetLiveObject_1c3bc0((s32)arg0, *(s32 *)((u8 *)arg0 + 0x4344)) != 0) {
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
