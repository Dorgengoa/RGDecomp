/* rgp:protos */
#line 1
#include "types.h"

class VO {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v438(s32 x) { VCM(void, (void *, s32), 0x438, x); }
};

struct A {
    s16 id;
    s16 x2;
    s16 x4;
    u8 x6;
    u8 pad7[0x64 - 7];
    s16 x64;
    u8 b0 : 1;
    u8 b1 : 1;
};

struct H {
    u8 pad0[0x1E];
    u8 x1E;
    u8 pad1F;
    s32 x20;
};

struct O {
    u8 pad0[0x4F0];
    s32 x4F0;
    u8 pad4F4[0x4FC - 0x4F4];
    s32 x4FC;
    u8 pad500[0x518 - 0x500];
    u8 *x518;
    u8 pad51C[0x534 - 0x51C];
    s32 x534;
};

struct G {
    u8 pad0[0x1C];
    s32 x1C;
};

extern "C" {
void CharaResLoadDispatch_1f4420(A *, u8 *, s32);
void CharaResRecRelease_1f4510(A *, u8 *, s32);
s32 GetCharaDataMgr_1fdb70();
H *CharaDataFindNode_1ed6d0(s32, s32, s32, s32);
O *ObjRecGetLiveObject_1c4a90(u8 *, s32);
s32 GameSceneSoundSlot1GetHandle_1d07b0(u8 *);
s32 GetActionMgr_1fdb50();
s32 ActionMgrFindById_233b50(s32, s32);
s32 CharaIsDeadVanishedMaybe_210a90(s32);
void ActionMgrRemoveChara_233dc0(s32, s32);
G *GetGameData_1fede0();
VO *ObjFindById_3bb3a0(s32, s32);
}

extern "C" void CharaResRecUpdate_1f48a0(A *a, u8 *arg1, s32 arg2)
{
    H *h;
    O *o;
    s32 id;
    bool ok;
    s32 g;
    s32 v;
    VO *vo;

    if (a->id < 0) {
        return;
    }
    if (a->x64 == 4) {
        return;
    }
    if (!(a->x6 & 0x80)) {
        CharaResLoadDispatch_1f4420(a, arg1, arg2);
    }
    if (a->b0) {
        h = CharaDataFindNode_1ed6d0(GetCharaDataMgr_1fdb70(), a->x4, 5, 5);
        o = ObjRecGetLiveObject_1c4a90(arg1, a->id);
        if (h != 0 && o != 0) {
            if (h->x20 != -1) {
                o->x4FC = h->x20;
                o->x518 = arg1 + 0xB0A4;
                o->x4F0 = GameSceneSoundSlot1GetHandle_1d07b0(arg1);
                a->b0 = 0;
                o->x534 = 0;
            }
        } else if (h != 0 && h->x1E == 4) {
            a->b0 = 0;
        }
    }
    if (!a->b1) {
        return;
    }
    id = a->id;
    ok = true;
    g = GetActionMgr_1fdb50();
    v = ActionMgrFindById_233b50(g, id);
    if (v != 0 && ((unsigned char)CharaIsDeadVanishedMaybe_210a90(v)) == 0) {
        ok = false;
    }
    if (!ok) {
        return;
    }
    a->b1 = 0;
    ActionMgrRemoveChara_233dc0(g, id);
    CharaResRecRelease_1f4510(a, arg1, arg2);
    vo = ObjFindById_3bb3a0(GetGameData_1fede0()->x1C, id);
    if (vo != 0) {
        vo->v438(1);
    }
}
