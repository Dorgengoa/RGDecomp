#pragma opt_propagation off
#include "types.h"

void ModelSetPos_151110(s32, f32 *);
s32 GetActionMgr_1fdb50();
void CharaSetPos_213a40(s32, f32 *);
void CharaSetHomePos_214330(s32, f32 *);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaSetPosVec_2387a0(s32, f32 *);
s32 EventSceneGetObj_2676e0(s32);
f32 TaggedGetFloat_26a280(s32);
s32 ScriptGetInt_26a2a0(s32);
extern f32 D_0047E8D0;
extern f32 D_0047E8D4;
extern f32 D_0047E8D8;
extern f32 D_0047E8DC;

s32 EvCmdSetObjPos_267570(s64 *arg0, s32 arg1)
{
    f32 t[4];
    f32 v[3];
    s32 id;
    s32 obj;
    s32 r;
    s32 k;
    f32 *p;

    id = ScriptGetInt_26a2a0((s32)arg0++);
    obj = EventSceneGetObj_2676e0(id);
    if (obj == 0) {
        return 0;
    }
    v[0] = TaggedGetFloat_26a280((s32)arg0++);
    v[1] = TaggedGetFloat_26a280((s32)arg0++);
    v[2] = TaggedGetFloat_26a280((s32)arg0++);
    p = t;
    p[0] = D_0047E8D0;
    p[1] = D_0047E8D4;
    p[2] = D_0047E8D8;
    p[3] = D_0047E8DC;
    t[0] = v[0];
    t[1] = v[1];
    t[2] = v[2];
    ModelSetPos_151110(obj, t);
    r = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
    if (r != 0) {
        k = 0;
        if (arg1 >= 5) {
            k = ScriptGetInt_26a2a0((s32)arg0);
        }
        switch (k) {
        case 0:
            CharaSetPosVec_2387a0(r, v);
            break;
        case 1:
            CharaSetPos_213a40(r, v);
            break;
        case 9999:
            CharaSetPos_213a40(r, v);
            CharaSetHomePos_214330(r, v);
            break;
        }
    }
    return 1;
}
