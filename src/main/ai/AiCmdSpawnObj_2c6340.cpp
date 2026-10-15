#include "types.h"
#undef NULL
#define NULL 0

typedef struct Arg { s32 a, b; } Arg;
typedef struct V4 { f32 x, y, z, w; } V4;

class Obj {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    s32 x4;
    s32 x8;
    s32 xC;
};

extern "C" {
s32 GetActionMgr_1fdb50(void);
u8 *ActionMgrFindById_233b50(s32 arg0, s32 arg1);
void CharaSetPosVec_2387a0(u8 *arg0, V4 *arg1);
void ScriptSlotStoreIntRef_2cc900(Arg *arg0, s32 arg1);
f32 ScriptSlotGetFloat_2cc9a0(Arg *arg0);
s32 ScriptSlotGetInt_2cc9c0(Arg *arg0);
Obj *ObjSpawnTreeValidated_2f3370(s32 arg0);
}

extern "C" s32 AiCmdSpawnObj_2c6340(Arg *arg0, s32 arg1)
{
    V4 v;
    Obj *o;
    u8 *e;

    if (arg1 < 2) {
        return 0;
    }
    o = ObjSpawnTreeValidated_2f3370(ScriptSlotGetInt_2cc9c0(arg0++));
    if (o != NULL) {
        ScriptSlotStoreIntRef_2cc900(arg0++, o->xC);
        o->v1C();
        if (arg1 >= 5) {
            v.x = ScriptSlotGetFloat_2cc9a0(arg0++);
            v.y = ScriptSlotGetFloat_2cc9a0(arg0++);
            v.z = ScriptSlotGetFloat_2cc9a0(arg0++);
            e = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), o->xC);
            CharaSetPosVec_2387a0(e, &v);
            *(s32 *)(e + 0xA44) |= 0x01000000;
        }
    } else {
        ScriptSlotStoreIntRef_2cc900(arg0, -1);
    }
    return 1;
}
