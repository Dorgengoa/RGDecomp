#include "types.h"

extern void FrameGetWorldPos_148f30(s32, f32 *);
extern void FrameTransformPoint_148f60(s32, f32 *, f32 *);
extern s32 ModelGetFrame_1511f0(s32, s32);
extern s32 ModelFindFrameIndexByName_151220(s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void ScriptSlotStoreVec3_334790(s32, f32 *);
extern s32 ScriptSlotGetCodeAddr_334870(s32);
extern f32 ScriptSlotGetFloat_334890(s32);
extern s32 ScriptSlotGetInt_3348b0(s32);
extern f32 D_0047F4D0;
extern f32 D_0047F4D4;
extern f32 D_0047F4D8;
extern f32 D_0047F4DC;

s32 ScriptCmdGetNodePos_333700(s64 *arg0, s32 arg1)
{
    s32 id;
    s32 obj;
    s32 r;
    s32 t;
    f32 v[4];
    f32 *pv;

    if (arg1 != 5 && arg1 != 8) {
        return 0;
    }
    id = ScriptSlotGetInt_3348b0((s32)arg0++);
    obj = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id);
    if (obj == 0) {
        return 0;
    }
    t = *(s32 *)arg0;
    r = 0;
    if (t == 2) {
        r = ModelGetFrame_1511f0(obj, ModelFindFrameIndexByName_151220(obj, ScriptSlotGetCodeAddr_334870((s32)arg0++)));
    } else if (t == 0) {
        r = ModelGetFrame_1511f0(obj, ScriptSlotGetInt_3348b0((s32)arg0++));
    }
    if (r == 0) {
        return 0;
    }
    pv = v;
    v[0] = D_0047F4D0;
    v[1] = D_0047F4D4;
    v[2] = D_0047F4D8;
    v[3] = D_0047F4DC;
    if (arg1 == 5) {
        FrameGetWorldPos_148f30(r, pv);
    } else if (arg1 == 8) {
        v[0] = ScriptSlotGetFloat_334890((s32)arg0++);
        v[1] = ScriptSlotGetFloat_334890((s32)arg0++);
        v[2] = ScriptSlotGetFloat_334890((s32)arg0++);
        v[3] = 1.0f;
        FrameTransformPoint_148f60(r, v, v);
    }
    ScriptSlotStoreVec3_334790((s32)arg0, v);
    return 1;
}
