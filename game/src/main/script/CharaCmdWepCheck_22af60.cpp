#include "types.h"
extern "C" {

class VT {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * f(s32 a0) { return VCM(void *, (void *, s32), 0x384, a0); }
};

void GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
u8 *GetGameData_1fede0(void);
s32 CharaCmdRunIfElseEvnt_22e480(s32, s32, u8 *, s32);
s32 ActionMgrFindById_233b50(s32, s32);
s32 ScriptArgGetInt_302d70(u8 *);
VT *CharaMgrPoolFindById_3a8c60(s32, s32);

static inline bool chk(VT *t, u8 *arg1)
{
    u8 *q;
    bool r;

    r = false;
    q = (u8 *)t->f(ScriptArgGetInt_302d70(arg1));
    if (q != NULL) {
        if (*(s8 *)(*(u8 **)(q + 0x10) + 3) == ScriptArgGetInt_302d70(arg1 + 5)) {
            r = true;
        }
    }
    return r;
}
s32 CharaCmdWepCheck_22af60(s32 *arg0, u8 *arg1, s32 arg2) {
    s32 f;
    VT *temp_2;

    if ((arg2 != 3) && (arg2 != 4)) {
        return 1;
    }
    if (ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0) == 0) {
        return 1;
    }
    f = false;
    temp_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)(GetGameData_1fede0() + 0x14), *arg0);
    if (temp_2 != NULL) {
        f = chk(temp_2, arg1);
    }
    GetCurrentScene_1f5be0();
    return CharaCmdRunIfElseEvnt_22e480(*arg0, f, arg1 + 0xA, arg2 - 2);
}

}
