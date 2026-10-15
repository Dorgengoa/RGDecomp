#include "types.h"

extern void ModelSetRot_151080(s32, f32 *);
extern s32 GetActionMgr_1fdb50(void);
extern void CharaSetYaw_2138f0(s32, f32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaSetRotFromVec_2387b0(s32, f32 *);
extern s32 EventSceneGetObj_2676e0(s32);
extern f32 TaggedGetFloat_26a280(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern f32 D_0047D1FC;
extern f32 D_0047DCD8;
extern f32 D_0047DD40;

typedef struct { s32 a; s32 b; } E8;

s32 EvCmdSetObjRot_267370(E8 *arg0, s32 arg1)
{
    f32 comp[4];
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_4;
    s32 var_2;
    s32 var_3;
    f32 step;
    f32 lo;
    f32 hi;

    temp_2 = ScriptGetInt_26a2a0((s32) arg0++);
    temp_2_2 = EventSceneGetObj_2676e0(temp_2);
    if (temp_2_2 == 0) {
        return 0;
    }
    comp[0] = TaggedGetFloat_26a280((s32) arg0++);
    comp[1] = TaggedGetFloat_26a280((s32) arg0++);
    comp[2] = TaggedGetFloat_26a280((s32) arg0++);
    comp[3] = 1.0f;
    step = D_0047DCD8;
    lo = D_0047DD40;
    hi = D_0047D1FC;
    var_3 = 0;
    while (var_3 < 3) {
        while (comp[var_3] < lo) {
            comp[var_3] = comp[var_3] + step;
        }
        while (hi < comp[var_3]) {
            comp[var_3] = comp[var_3] - step;
        }
        var_3 += 1;
    }
    ModelSetRot_151080(temp_2_2, comp);
    temp_2_4 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), temp_2);
    if (temp_2_4 != 0) {
        var_2 = 0;
        if (arg1 >= 5) {
            var_2 = ScriptGetInt_26a2a0((s32) arg0);
        }
        switch (var_2) {
        case 0:
            CharaSetRotFromVec_2387b0(temp_2_4, comp);
            break;
        case 1:
            CharaSetYaw_2138f0(temp_2_4, comp[1]);
            break;
        }
    }
    return 1;
}
