#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 GetCurrentScene_1f5be0(void);
extern void *ObjRecGetLiveObject_1c3bc0(s32, s32);
extern f32 ScriptSlotGetFloat_334890(E8 *);
extern void CameraShakeStart_3058c0(void *, f32, f32, f32, f32);

s32 ScriptCmdCameraQuake_332480(E8 *p0, s32 p1)
{
    s32 r;
    void *o;
    f32 a;
    f32 b;
    f32 c;
    f32 d;

    if (p1 != 4) {
        return 0;
    }
    r = GetCurrentScene_1f5be0();
    if (r == 0) {
        return 0;
    }
    o = ObjRecGetLiveObject_1c3bc0(r, 1);
    if (o == 0) {
        return 0;
    }
    a = ScriptSlotGetFloat_334890(p0);
    b = ScriptSlotGetFloat_334890(p0 + 1);
    c = ScriptSlotGetFloat_334890(p0 + 2);
    d = ScriptSlotGetFloat_334890(p0 + 3);
    CameraShakeStart_3058c0(o, a, b, c, d);
    return 1;
}
