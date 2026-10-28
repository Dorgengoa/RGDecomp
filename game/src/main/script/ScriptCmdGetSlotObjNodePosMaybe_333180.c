/* rgp:protos */
#define RGP_SELF_ScriptCmdGetSlotObjNodePosMaybe_333180 1
#define RGP_SELF_getid2_333180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Buf50_333180 {
    u8 data[0x10];
} Buf50_333180;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline s32 getid2_333180(s32 base, s32 idx)
{
    return (idx >= 0 && idx < 0xC) ? base + ((idx * 4) + 0xC) : -1;
}

s32 ScriptCmdGetSlotObjNodePosMaybe_333180(s64 *arg0, s32 arg1) {
    Buf50_333180 sp50 __attribute__((aligned(16)));
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
    obj = ((s32)ObjRecGetLiveObject_1c4a90(ctx, id));
    if (obj == 0) {
        return 0;
    }
    obj2 = ((s32)ModelGetFrame_1511f0(obj, ModelFindFrameIndexByName_151220(obj, key)));
    if (obj2 == 0) {
        return 0;
    }
    FrameGetWorldPos_148f30(obj2, &sp50);
    ScriptSlotStoreVec3_334790((s32)arg0, &sp50);
    return 1;
}
