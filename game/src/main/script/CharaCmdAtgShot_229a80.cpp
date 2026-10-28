/* rgp:protos */
#line 1
#include "types.h"

struct V229a80b {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 ff0(s32 a0) { return VCM(s32, (void *, s32), 0xF0, a0); }
};
struct V229a80 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f274(s32 a0) { return VCM(s32, (void *, s32), 0x274, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    V229a80b * f384(bool a0) { return VCM(V229a80b *, (void *, bool), 0x384, a0); }
};

extern "C" {
s32 GetActionMgr_1fdb50();
void *GetGameData_1fede0(void);
s32 CharaGetBaseActionMode_213830(s32);
void CharaClearActionGaugeUsed_214000(s32);
void CharaSetActAbortCodeMaybe_2149a0(s32, s32);
s32 CharaGetActAbortCodeMaybe_2149b0(s32);
s32 CharaGetActionTable_214cd0(s32);
s32 CharaCmdRunIfElseEvnt_22e480(s32, bool, s32, s32);
s32 ActionMgrFindById_233b50(s32, s32);
V229a80 *CharaMgrPoolFindById_3a8c60(s32, s32);
}

extern "C" s32 CharaCmdAtgShot_229a80(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 h;
    bool ok;
    V229a80 *o;

    h = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (h == 0) {
        return 1;
    }
    if (CharaGetActionTable_214cd0(h) == 0) {
        return 1;
    }
    ok = false;
    if (CharaGetActAbortCodeMaybe_2149b0(h) == 0) {
        ok = true;
        o = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)GetGameData_1fede0() + 0x14), *arg0);
        if (o != 0) {
            if (o->f384(((short)CharaGetBaseActionMode_213830(h)) != 2)->ff0(0) <= 0 || o->f274(-1) == 0) {
                CharaSetActAbortCodeMaybe_2149a0(h, 2);
                CharaClearActionGaugeUsed_214000(h);
                ok = false;
            }
        }
    }
    return CharaCmdRunIfElseEvnt_22e480(*arg0, ok, arg1, arg2);
}
