#include "types.h"
typedef struct { s32 a, b; } E8_2ca1a0;
extern s32 ScriptSlotGetInt_2cc9c0(E8_2ca1a0 *);
extern s32 ScriptSlotGetCodeAddr_2cc980(E8_2ca1a0 *);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 ModelFindFrameIndexByName_151220(s32, s32);
extern void ScriptSlotStoreIntRef_2cc900(E8_2ca1a0 *, s32);
extern struct { s32 v; s32 pad[3]; } D_004DB920;

s32 AiCmdObjFindFrameIndex_2ca1a0(E8_2ca1a0 *p0)
{
    s32 a;
    s32 b;
    s32 r;
    s32 v;

    a = ScriptSlotGetInt_2cc9c0(p0++);
    b = ScriptSlotGetCodeAddr_2cc980(p0++);
    r = ObjRecGetLiveObject_1c4a90(D_004DB920.v, a);
    if (r == 0) {
        return 0;
    }
    v = ModelFindFrameIndexByName_151220(r, b);
    ScriptSlotStoreIntRef_2cc900(p0, v);
    return 1;
}
