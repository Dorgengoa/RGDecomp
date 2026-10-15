#include "types.h"

typedef struct Buf50_333180 {
    u8 data[0x10];
} Buf50_333180;

extern void FrameGetWorldPos_148f30(s32, Buf50_333180 *);
extern s32 ModelGetFrame_1511f0(s32, s32);
extern s32 ModelFindFrameIndexByName_151220(s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void *GetGameData_1fede0(void);
extern void ScriptSlotStoreVec3_334790(s32, Buf50_333180 *);
extern s32 ScriptSlotGetCodeAddr_334870(s32);
extern s32 ScriptSlotGetInt_3348b0(s32);

static inline s32 getid2_333180(s32 base, s32 idx)
{
    return (idx >= 0 && idx < 0xC) ? base + ((idx * 4) + 0xC) : -1;
}

s32 ScriptCmdGetSlotObjNodePosMaybe_333180(s64 *arg0, s32 arg1) {
    Buf50_333180 sp50;
    s32 idx;
    s32 base;
    s32 key;
    s32 ctx;
    s32 id;
    s32 obj;
    s32 obj2;

    if (arg1 != 6) {
        return 0;
    }
    idx = ScriptSlotGetInt_3348b0((s32)arg0++);
    base = ScriptSlotGetInt_3348b0((s32)arg0++);
    key = ScriptSlotGetCodeAddr_334870((s32)arg0++);
    GetGameData_1fede0();
    ctx = GetCurrentScene_1f5be0();
    id = getid2_333180(base, idx);
    obj = ObjRecGetLiveObject_1c4a90(ctx, id);
    if (obj == 0) {
        return 0;
    }
    obj2 = ModelGetFrame_1511f0(obj, ModelFindFrameIndexByName_151220(obj, key));
    if (obj2 == 0) {
        return 0;
    }
    FrameGetWorldPos_148f30(obj2, &sp50);
    ScriptSlotStoreVec3_334790((s32)arg0, &sp50);
    return 1;
}
