#include "types.h"

typedef struct { s32 x, y, z; } V259c90;
extern s32 MotionListFindByName_1721d0(V259c90 *, s32, s32 *, s32 *);
extern u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void ScriptSetRefInt_26a1e0(s32, s32);
extern s32 ScriptGetCodeAddr_26a200(s32);
extern s32 ScriptGetInt_26a2a0(s32);

s32 EvCmdObjHasMotion_259c90(s64 *arg0, s32 arg1)
{
    V259c90 v;
    s32 s1;
    s32 s2;
    s32 a;
    s32 b;
    u8 *t;

    if (arg1 != 3) {
        return 0;
    }
    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetCodeAddr_26a200((s32)arg0++);
    ScriptSetRefInt_26a1e0((s32)arg0, 0);
    t = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), a);
    if (t == NULL) {
        return 1;
    }
    v.x = *(s32 *)(t + 0x1F0);
    v.y = *(s32 *)(t + 0x1F4);
    v.z = *(s32 *)(t + 0x1F8);
    if (MotionListFindByName_1721d0(&v, b, &s1, &s2) != 0) {
        ScriptSetRefInt_26a1e0((s32)arg0, 1);
    }
    return 1;
}
