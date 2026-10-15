#include "camera_cpp.h"

typedef struct SceneMgr {
    u8 pad0000[0x4344];
    s32 cameraId;
} SceneMgr;

extern "C" Camera *ObjRecGetLiveObject_1c3bc0(SceneMgr *mgr, s32 id);
extern "C" void GameSceneCameraPush_1ced50(SceneMgr *mgr);
extern "C" SceneMgr *GetCurrentScene_1f5be0(void);
extern "C" void CameraModeSetTop_309440(Camera *, s32);

extern "C" void CameraSwitchTo2KeepView_309fa0(void)
{
    Vec4 eye;
    Vec4 at;
    SceneMgr *mgr;
    Camera *cur;
    Camera *nw;

    mgr = GetCurrentScene_1f5be0();
    cur = ObjRecGetLiveObject_1c3bc0(mgr, mgr->cameraId);
    nw = ObjRecGetLiveObject_1c3bc0(mgr, 2);
    if (cur == NULL || nw == NULL) {
        return;
    }
    cur->getEyeLocal(&eye);
    cur->getAtLocal(&at);
    GameSceneCameraPush_1ced50(mgr);
    mgr->cameraId = 2;
    nw->setEye(&eye);
    nw->setAt(&at);
    nw->setAngle(cur->getAngle());
    nw->unk70 = cur->unk70;
    CameraModeSetTop_309440(nw, 5);
    *(s32 *)((u8 *)nw + 0x270) = -1;
}
