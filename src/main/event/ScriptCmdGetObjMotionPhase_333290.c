#include "types.h"

typedef struct { s32 a, b; } T_00333290;

extern void *GetCurrentScene_1f5be0(void);
extern s32 ScriptSlotGetInt_3348b0(T_00333290 *);
extern void *ObjRecGetLiveObject_1c4a90(void *, s32);
extern f32 ModelObjGetMotionPhase_1add70(void *);
extern void ScriptSlotStoreFloatRef_3347d0(T_00333290 *, f32);

s32 ScriptCmdGetObjMotionPhase_333290(T_00333290 *q)
{
    void *s;
    s32 n;
    void *r;

    s = GetCurrentScene_1f5be0();
    n = ScriptSlotGetInt_3348b0(q++);
    r = ObjRecGetLiveObject_1c4a90(s, n);
    if (r != 0) {
        ScriptSlotStoreFloatRef_3347d0(q, ModelObjGetMotionPhase_1add70(r));
    } else {
        ScriptSlotStoreFloatRef_3347d0(q, -1.0f);
    }
    return 1;
}
