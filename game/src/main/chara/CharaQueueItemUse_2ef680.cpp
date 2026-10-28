/* rgp:protos */
#line 1
#include "types.h"

class Handler {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Attach(void * a0) { VCM(void, (void *, void *), 0x280, a0); }
};

struct Mgr {
    u8 pad[0x18];
    s32 unk18;
};

struct Ent {
    s16 unk0;
    u8 pad2[0x6C - 2];
    s32 unk6C;
    s8 unk70;
    s8 unk71;
};

extern "C" {
s32 GetActionMgr_1fdb50(void);
Mgr *GetGameData_1fede0(void);
Ent *CharaGetExecInfo_2149f0(s32);
void CharaExecInfoInit_219100(Ent *);
s32 ActionMgrFindById_233b50(s32, s32);
s32 ExecInfoInitFromInvItem_3a7430(Ent *, s32, s32, s32);
Handler * ActorCastToUnit_3b8770(s32, int, int, int);
Handler * ActorCastToChara_3b87b0(s32, int, int, int);
s32 PartyAllIncapacitated_3c07c0(s32, s32);
s32 ActorFindById_3eb870(Mgr *, s32);
}

extern "C" s32 CharaQueueItemUse_2ef680(s32 arg0, s32 arg1, s32 arg2, s8 arg3, s32 arg4)
{
    Mgr *o;
    s32 h;
    s32 id;
    s32 r;
    Ent *e;
    Handler *p;
    bool found;

    o = GetGameData_1fede0();
    h = GetActionMgr_1fdb50();
    id = ActorFindById_3eb870(o, arg0);
    if (id == 0) {
        return 0;
    }
    r = ActionMgrFindById_233b50(h, arg0);
    if (r == 0) {
        return 0;
    }
    e = CharaGetExecInfo_2149f0(r);
    CharaExecInfoInit_219100(e);
    if (PartyAllIncapacitated_3c07c0(o->unk18, 1) != 0) {
        return 0;
    }
    if (ExecInfoInitFromInvItem_3a7430(e, arg0, arg1, 0) == 0) {
        return 0;
    }
    e->unk71 = arg3;
    if (arg4 != -1) {
        e->unk0 = arg4;
    }
    found = false;
    p = ActorCastToChara_3b87b0(id, 0, 0, 0);
    if (p != 0) {
        p->Attach(e);
        found = true;
    }
    p = ActorCastToUnit_3b8770(id, 0, 0, 0);
    if (p != 0) {
        p->Attach(e);
        found = true;
    }
    if (!found) {
        CharaExecInfoInit_219100(e);
        return 0;
    }
    e->unk6C = arg2;
    e->unk70 = 1;
    return 1;
}
