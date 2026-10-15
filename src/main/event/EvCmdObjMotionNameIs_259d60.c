#include "types.h"
typedef struct { s32 a, b; } E8_259d60;
extern s32 ScriptGetInt_26a2a0(E8_259d60 *);
extern s32 ScriptGetCodeAddr_26a200(E8_259d60 *);
extern void ScriptSetRefInt_26a1e0(E8_259d60 *, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 ModelObjGetMotionName_1add90(s32);
extern s32 strcmp(s32, s32);

s32 EvCmdObjMotionNameIs_259d60(E8_259d60 *p0, s32 p1)
{
    s32 a;
    s32 b;
    s32 o;
    s32 s;

    if (p1 != 3) {
        return 0;
    }
    a = ScriptGetInt_26a2a0(p0++);
    b = ScriptGetCodeAddr_26a200(p0++);
    ScriptSetRefInt_26a1e0(p0, 0);
    o = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), a);
    if (o == 0) {
        return 1;
    }
    s = ModelObjGetMotionName_1add90(o);
    if (s == 0) {
        return 1;
    }
    if (strcmp(s, b) == 0) {
        ScriptSetRefInt_26a1e0(p0, 1);
    }
    return 1;
}
