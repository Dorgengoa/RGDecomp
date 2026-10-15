#include "types.h"

f32 Atan2f_1291a8(f32, f32);
f32 AngleWrap_1cbf30(f32);
s32 GetActionMgr_1fdb50();
s32 CharaSetYaw_2138f0(s32, f32);
u8 *CharaGetHitInfo_214a00(s32);
s32 ActionMgrFindById_233b50(s32, s32);
f32 ScriptArgGetFloat_302cf0(s32);
extern f32 D_0047D1FC;

s32 CharaCmdDamageDir_22c9a0(s32 *arg0, s32 arg1, s32 arg2)
{
    f32 f;
    s32 id;
    u8 *p;

    if (arg2 != 0) {
        return 1;
    }
    id = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (id == 0) {
        return 1;
    }
    p = CharaGetHitInfo_214a00(id);
    if (*(f32 *)(p + 0x10) == 0.0f && *(f32 *)(p + 0x18) == 0.0f) {
        return 1;
    }
    f = 0.0f;
    if (arg2 > 0) {
        f = ScriptArgGetFloat_302cf0(arg1);
    }
    CharaSetYaw_2138f0(id, AngleWrap_1cbf30(D_0047D1FC + (f + Atan2f_1291a8(*(f32 *)(p + 0x10), *(f32 *)(p + 0x18)))));
    return 1;
}
