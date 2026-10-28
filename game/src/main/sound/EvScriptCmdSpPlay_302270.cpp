/* rgp:protos */
#line 1
#include "types.h"

#undef NULL
#define NULL 0
extern "C" {

s32 StrEqualNonNull_1ca6c0(s32, s32);
s32 GetActionMgr_1fdb50(void);
void * GetGameData_1fede0(void);
void StreamPlayMwv_207340(s32, s32, f32);
s32 CharaEvObjContactFlag1Related_214920(s32);
s32 *CharaGetEvObjContact_214990(s32);
s32 ActionMgrFindById_233b50(s32, s32);
s32 GetEventObjMgr_2d1960(void);
s32 EventRecGetKey_2e5730(void *);
s32 EventObjMgrSpPlayAllowedMaybe_2e79f0(void);
f32 ScriptArgGetFloat_302cf0(s32);
s32 ScriptArgGetInt_302d70(s32);
s32 EvObjLiftGetPlayState_336120(void *);
s32 StateFlagTest_3ccd70(s32, s32);

extern "C++" { class VC_0 {
public:
    u8 pad[0xDC];
    VC_VPTR_MEMBER; template <class... VcA> s32 f(VcA... vc_va) { return VCM_FN(s32, (void *, ...), 0x8)((void *)this, vc_va...); }
}; }
s32 EvScriptCmdSpPlay_302270(void *arg0, s32 arg1, s32 arg2, int rgp_a3) {
    f32 f;
    s32 *p;
    s32 a;
    s32 n;
    s32 b;
    void *o;
    void *t;

    o = (void *)((*(s32 *)((u8 *)(arg0) + 0x4)));
    if (o != NULL) {
        switch (((VC_0 *)(o))->f()) {
        case 9:
            if (StateFlagTest_3ccd70((*(s32 *)((u8 *)(GetGameData_1fede0()) + 0x10)), 0x7EE) != 0) {
                return 1;
            }
            break;
        case 4:
            if (((short)EvObjLiftGetPlayState_336120(o)) == 7) {
                return 1;
            }
            break;
        case 1:
            t = GetGameData_1fede0();
            n = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), (*(s16 *)((u8 *)((*(void **)((u8 *)(t) + 0x18))) + 0x18E)));
            if (n == 0) {
                return 1;
            }
            if (CharaEvObjContactFlag1Related_214920(n) == 0) {
                return 1;
            }
            p = CharaGetEvObjContact_214990(n);
            if (((unsigned char)StrEqualNonNull_1ca6c0(*p, EventRecGetKey_2e5730(o))) == 0) {
                return 1;
            }
            break;
        }
    }
    if ((arg2 != 1) && (arg2 != 2) && (arg2 != 3)) {
        return 1;
    }
    if (((void)(GetEventObjMgr_2d1960()), EventObjMgrSpPlayAllowedMaybe_2e79f0()) != 0) {
        a = ScriptArgGetInt_302d70(arg1);
        if (arg2 > 1) {
            f = ScriptArgGetFloat_302cf0(arg1 + 5);
        } else {
            f = 1.0f;
        }
        if (arg2 > 2) {
            b = ScriptArgGetInt_302d70(arg1 + 0xA);
        } else {
            b = 0;
        }
        StreamPlayMwv_207340(a, b != 0, f);
    }
    return 1;
}

}
