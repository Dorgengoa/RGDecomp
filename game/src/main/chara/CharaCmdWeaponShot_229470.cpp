/* rgp:protos */
#line 1
#include "types.h"

class VR {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void fF0(s32 a0) { VCM(void, (void *, s32), 0xF0, a0); }
};

class VQ {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    VR * f384(s32 a0) { return VCM(VR *, (void *, s32), 0x384, a0); }
};

extern "C" s32 GetActionMgr_1fdb50(void);
extern "C" void *GetGameData_1fede0(void);
extern "C" s32 CharaGetBaseActionMode_213830(s32);
extern "C" s32 ActionMgrFindById_233b50(s32, s32);
extern "C" VQ *CharaMgrPoolFindById_3a8c60(s32, s32);

extern "C" s32 CharaCmdWeaponShot_229470(s32 *arg0)
{
    s32 t;
    VQ *o;

    t = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (t == 0) {
        return 1;
    }
    o = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)GetGameData_1fede0() + 0x14), *arg0);
    if (o == 0) {
        return 1;
    }
    o->f384(((short)CharaGetBaseActionMode_213830(t)) != 2)->fF0(0);
    return 1;
}
