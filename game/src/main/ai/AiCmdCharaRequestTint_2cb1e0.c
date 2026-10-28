/* rgp:protos */
#define RGP_SELF_AiCmdCharaRequestTint_2cb1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct E { s32 a; s32 b; };

s32 AiCmdCharaRequestTint_2cb1e0(struct E *p, s32 count)
{
    s32 obj;
    s32 a;
    s32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 f;
    f32 g;

    if (count < 7) {
        return 1;
    }
    obj = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), ScriptSlotGetInt_2cc9c0(p++)));
    if (obj == 0) {
        return 1;
    }
    a = ScriptSlotGetInt_2cc9c0(p++);
    b = ScriptSlotGetInt_2cc9c0(p++);
    c = (f32)ScriptSlotGetInt_2cc9c0(p++);
    d = (f32)ScriptSlotGetInt_2cc9c0(p++);
    e = (f32)ScriptSlotGetInt_2cc9c0(p++);
    f = (f32)ScriptSlotGetInt_2cc9c0(p++);
    g = 1.0f;
    if (count >= 8) {
        g = ScriptSlotGetFloat_2cc9a0(p);
    }
    CharaRequestTint_213fd0(obj, a, b, c, d, e, f, g);
    return 1;
}
